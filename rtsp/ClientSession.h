#ifndef RTSP_CLIENTSESSION_H
#define RTSP_CLIENTSESSION_H

#include "SocketHandler.h"
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <mutex>
#include <chrono>

using namespace std;

class ClientSession {
public:
    ClientSession(int sessionId);

    // 세션 ID 반환
    int getSessionId() const;

    // 클라이언트 상태 반환
    int getVersion() const;

    // 클라이언트 상태 반환
    string getState() const;

    pair<int, int> getPort() const;
    void setPort(int port1, int port2);

    // 클라이언트 상태 설정 (SETUP, PLAY, PAUSE 등)
    void setState(const string& newState);

private:
    int sessionId;                    // 세션 ID
    int rtpPort, rtcpPort;            // RTP/RTCP 포트 정보
    int version;
    string state;                // 클라이언트 상태 (SETUP, PLAY, PAUSE 등)

    queue<string> mediaBuffer; // 미디어 프레임 큐
    chrono::time_point<chrono::system_clock> lastActivity; // 마지막 활동 시간
    const double sessionTimeout = 60.0;  // 세션 타임아웃 시간 (초)

    mutex sessionMutex;          // 세션 동기화용 뮤텍스
};

#endif //RTSP_CLIENTSESSION_H