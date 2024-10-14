#ifndef RTSP_MEDIASTREAMHANDLER_H
#define RTSP_MEDIASTREAMHANDLER_H

#include "SocketHandler.h"
#include <condition_variable>
#include <atomic>
#include <alsa/asoundlib.h>

using namespace std;

class MediaStreamHandler {
public:
    MediaStreamHandler(SocketHandler& socketHandler);

    void handleMediaStream();

    unsigned char linearToUlaw(int sample);
    void initAlsa(snd_pcm_t*& pcmHandle, snd_pcm_hw_params_t*& params, int& rc, int& sampleRate, int& dir);
    int captureAudio(snd_pcm_t*& pcmHandle, unsigned char*& buffer, int& frames, int& rc, unsigned char*& payload);

    void playStreaming();
    void pauseStreaming();
    void teardown();

private:
    SocketHandler& socketHandler;
    atomic<bool> isStreaming;
    atomic<bool> isPaused;

    mutex mtx;  // 상태 보호용 뮤텍스
    condition_variable condition;  // 스트리밍 상태 제어용 조건 변수
};

#endif //RTSP_MEDIASTREAMHANDLER_H
