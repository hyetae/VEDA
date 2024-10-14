#include "Protos.h"
#include "utils.h"
#include "SocketHandler.h"
#include "MediaStreamHandler.h"

#include <iostream>
#include <cstdint>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <utility>
#include <random>

using namespace std;

MediaStreamHandler::MediaStreamHandler(SocketHandler& socketHandler)
            : socketHandler(socketHandler), isStreaming(false), isPaused(false) {}

// RTP 및 RTCP를 주기적으로 처리하는 루프
void MediaStreamHandler::handleMediaStream() {
    Protos protos(utils::genSeqNum(), utils::genSSRC());

    snd_pcm_t* pcmHandle;
    snd_pcm_hw_params_t* params;
    int rc, dir;
    unsigned int sampleRate = 8000 ; // G.711의 샘플링 레이트
    size_t payloadSize = 160;  // 20ms당 160 샘플
    int frames = payloadSize;  // G.711은 8kHz에서 20ms당 160 샘플
    auto buffer = new short[payloadSize];
    auto payload = new unsigned char[payloadSize];

    initAlsa(pcmHandle, params, rc, sampleRate, dir);
        if (rc < 0) {
        fprintf(stderr, "ALSA initialization failed\n");
        exit(1);
    }

    unique_lock<std::mutex> lock(mtx);

    while (isStreaming) {
        // 스트리밍을 재개하는 신호를 기다림
        condition.wait(lock, [this] { return !isPaused || !isStreaming; });

        if (!isStreaming) break;  // TEARDOWN 요청 시 종료

        // RTP 패킷 전송 (예시)
        if (!isPaused) {
            cout << "오디오 캡처" << endl;
            if (captureAudio(pcmHandle, buffer, frames, rc, payload) < 0) {
                cerr << "오디오 캡처 실패..." << endl;
                break;
            }
            cout << "오디오 성공" << endl;

            cout << "RTP 패킷 생성" << endl;
            auto RTPPacket = protos.createRTPPacket(payload);
            cout << "RTP 패킷 전송" << endl;
            socketHandler.sendRTPPacket(RTPPacket);

            // 10 패킷마다 RTCP SR 전송
            if (protos.getPacketCount() % 10 == 0) {
                cout << "Sender Report 생성" << endl;
                auto sr = protos.createSR();
                socketHandler.sendSenderReport(sr);
                cout << "Sender Report 전송" << endl;
            }

            this_thread::sleep_for(std::chrono::milliseconds(20));  // 20ms 지연 (50 패킷/초)
        }
    }
    free(buffer);
    free(payload);
//    cout << "RTP/RTCP 스트리밍 종료" << endl;
}

unsigned char MediaStreamHandler::linearToUlaw(int sample) {
    const int MAX = 32767;
    const int BIAS = 0x84;
    int sign = (sample >> 8) & 0x80; // Sign bit
    if (sign != 0) sample = -sample;
    if (sample > MAX) sample = MAX;
    sample += BIAS;
    int exponent = 7;
    int mask;
    for (; exponent > 0; exponent--) {
        mask = 1 << (exponent + 3);
        if (sample >= mask) break;
    }
    int mantissa = (sample >> (exponent + 3)) & 0x0F;
    return ~(sign | (exponent << 4) | mantissa);
}

void MediaStreamHandler::initAlsa(snd_pcm_t*& pcmHandle, snd_pcm_hw_params_t*& params, int& rc, unsigned int& sampleRate, int& dir) {
    // PCM 장치 열기
    rc = snd_pcm_open(&pcmHandle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
        fprintf(stderr, "Unable to open PCM device: %s\n", snd_strerror(rc));
        return;  // exit 대신 함수 반환을 사용해 더 안전한 에러 처리
    }

    // 하드웨어 매개변수 구조체 할당 및 기본값 설정
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcmHandle, params);

    // 인터리브 모드 설정
    rc = snd_pcm_hw_params_set_access(pcmHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (rc < 0) {
        fprintf(stderr, "Error setting access mode: %s\n", snd_strerror(rc));
        return;
    }

    // 샘플 형식 설정 (16비트 리틀엔디안)
    rc = snd_pcm_hw_params_set_format(pcmHandle, params, SND_PCM_FORMAT_S16_LE);
    if (rc < 0) {
        fprintf(stderr, "Error setting format: %s\n", snd_strerror(rc));
        return;
    }

    // 모노 설정
    rc = snd_pcm_hw_params_set_channels(pcmHandle, params, 1);
    if (rc < 0) {
        fprintf(stderr, "Error setting channels: %s\n", snd_strerror(rc));
        return;
    }

    // 샘플 레이트 설정 (근사치)
    rc = snd_pcm_hw_params_set_rate_near(pcmHandle, params, &sampleRate, &dir);
    if (rc < 0) {
        fprintf(stderr, "Error setting sample rate: %s\n", snd_strerror(rc));
        return;
    }

    // 하드웨어 매개변수 적용
    rc = snd_pcm_hw_params(pcmHandle, params);
    if (rc < 0) {
        fprintf(stderr, "Unable to set HW parameters: %s\n", snd_strerror(rc));
        return;
    }

    // 성공적으로 초기화 완료
    printf("ALSA PCM device initialized with sample rate: %d\n", sampleRate);
}

int MediaStreamHandler::captureAudio(snd_pcm_t*& pcmHandle, short*& buffer, int& frames, int& rc, unsigned char*& payload) {
    // ALSA로부터 오디오 데이터 캡처
    rc = snd_pcm_readi(pcmHandle, buffer, frames);
    if (rc == -EPIPE) {
        // 오버런
        fprintf(stderr, "Overrun occurred\n");
        snd_pcm_prepare(pcmHandle);
        return -1;
    } else if (rc < 0) {
        fprintf(stderr, "Error from read: %s\n", snd_strerror(rc));
        return -1;
    } else if (rc != frames) {
        fprintf(stderr, "Short read, read %d frames\n", rc);
    }

    // 캡처한 데이터를 G.711 µ-law으로 인코딩
    for (int i = 0; i < frames; i++)
        payload[i] = linearToUlaw(buffer[i]);

    return 0;  // 정상적인 처리 시 0 반환
}

// 스트리밍 시작을 위한 상태 초기화 및 동작 시작
void MediaStreamHandler::playStreaming() {
    lock_guard<std::mutex> lock(mtx);
    isStreaming = true;
    isPaused = false;
    condition.notify_all();  // 스트리밍 시작 신호
    cout << "스트리밍 시작" << endl;
}

// PAUSE 요청 처리
void MediaStreamHandler::pauseStreaming() {
    lock_guard<std::mutex> lock(mtx);
    if (!isPaused) {
        isPaused = true;
        cout << "스트리밍 일시정지" << endl;
    }
}

// TEARDOWN 요청 처리 (스트리밍 중단)
void MediaStreamHandler::teardown() {
    lock_guard<std::mutex> lock(mtx);
    isStreaming = false;
    condition.notify_all();  // 모든 스레드 종료
    cout << "스트리밍 중단" << endl;
}