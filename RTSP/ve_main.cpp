#include "ve_main.h"

void rtp_rtcp_thread_run() {
    // rtp/rtcp thread에 필요한 여러 초기화 코드
    while (1) {
        // 현재 main thread에서 처리하기를 기다리는 RTSP 요청이 있는지 확인 후, 존재한다면 처리

        if (RTCP 패킷을 보낼 주기가 되면) {
            // RTCP Sender Report 전송
        }

        if (클라이언트 세션이 teardown||none||init)
            break;
        else if (클라이언트 세션이 ready)
            continue;

        // 파일에서 미디어 데이터를 읽음
        if (파일 끝에 도달하면)
            is_eof = 1;

        // 스트림 동기화를 위한 delay 시간 계산
        // 계산된 delay 시간만큼 지연

        // 파일에서 읽은 데이터로 RTP 패킷 생성 후 전송

        if (is_eof) {
            // RTCP bye 패킷 전송
            break;
        }
    }
}

void handle_rtp_trcp() {
    if (RTP 채널) {
        // RTSP 스트림 서버에서는 RTP 패킷 수신 x
    } else { // RTCP 채널이면
        // RTCP 패킷 파싱 후 처리
    }
}

void handle_options() {
    // 필요한 헤더들을 얻어서 처리
    // 요청 실패/성공 응답 메시지 생성
    // 메시지 전송
}

void handle_describe() {
    // Aceept header 반드시 존재, application/sdp
    // 그렇지 않으면 406(Not Acceptable)
    // SDP 포맷으로 RSTP DESCRIBE 메서드의 body 생성

    // 클라이언트 세션의 현재 상태를 init으로
    // 응답 메시지 생성 후 전송
}

void handle_setup() {
    // Transport Header 얻음
    // SETUP 요청에서 반드시 존재
    // 전송 방법이 UDP인 경우 461(Unsupported transport)

    // 클라이언트 세션의 현재 상태를 ready로

    // response header에 Transport header 추가
    // response header에 session header 추가

    // 응답 메시지 생성 후 전송

    // rtp/rtcp thread 생성
    rtp_rtcp_thread_run();
}

void handle_play() {
    // Session header 읽음, 반드시 존재

    if (session id 불일치) {
        // 454(Session Not Found)
    }

    // Range header
    // Scale header
    // Speed header

    // RTSP 상태 playing으로 설정 후 rtp/rtcp thread에서 처리하기를 최대 3초 대기

    // rtp/rtcp thread는 클라이언트 세션 상태를 playing으로 설정
}

static int handle_pause(vd_client_session* client_session) {
    // Session header 읽음, 반드시 존재

    if (session id 불일치) {
        // 454(Session Not Found)
    }

    // RTSP 상태 ready로 설정 후 rtp/rtcp thread에서 처리하기를 최대 3초 대기

    // rtp/rtcp thread는 클라이언트 세션 상태를 ready로 설정
}

void handle_teardown() {
    // Session header 읽음, 반드시 존재

    if (session id 불일치) {
        // 454(Session Not Found)
    }

    // RTSP 상태 teardown으로 설정 후 rtp/rtcp thread에서 처리하기를 최대 3초 대기

    // rtp/rtcp thread는 클라이언트 세션 상태를 teardown으로 설정
}

void handle_rtsp() {
    // RTSP 요청 파싱
    if (OPTIONS) {
        handle_options();
    } else if (DESCRIBE) {
        handle_describe();
    } else if (SETUP) {
        handle_setup();
    } else if (PLAY) {
        handle_play();
    } else if (PAUSE) {
        handle_pause();
    } else if (TEARDOWN) {
        handle_teardown();
    }
}

void main_thread_run() {
    // 클라이언트 세션을 메인 데이터 구조체에 추가

    while (1) { // 종료 조건이 참일 동안
        // 클라이언트에서 데이터를 읽음

        if (RTP/RTCP TCP 헤더인 4byte를 읽으면) {
            if (첫 문자가 $) { // RTP/RTCP 패킷이면
                // RTP/RTCP 채널과 실제 패킷 길이를 구함
                // 얻은 패킷 길이만큼 데이터를 얻음
                // RTP/RTCP 패킷 처리
                handle_rtp_trcp();
            } else { // RTSP 패킷이면
                // 위에서 얻은 4byte 복사
                // RTSP 요청을 받음
                // RTSP 요청은 \r\n\r\n로 끝나기 때문에 이 4byte를 연속으로 받을 때까지 데이터를 얻음
                // RTSP 요청 처리
                handle_rtsp();
            }
        }
    }
}