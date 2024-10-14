#ifndef RTSP_CLIENTSESSION_H
#define RTSP_CLIENTSESSION_H

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <mutex>
#include <chrono>

using namespace std;

class ClientSession {
public:
    ClientSession(int sessionId, int tcpSocket, int rtpPort, int rtcpPort);

    // 세션 ID 반환
    int getSessionId() const;

    // 클라이언트 상태 반환
    int getVersion() const;

    // 클라이언트 상태 반환
    string getState() const;

    pair<int, int> getPort() const;

    // 클라이언트 상태 설정 (SETUP, PLAY, PAUSE 등)
    void setState(const string& newState);

    // 미디어 버퍼에 프레임 추가
    void addFrameToBuffer(const string& frame);

    // 미디어 버퍼에서 프레임 가져오기
    string getFrameFromBuffer();

    // 세션 타임아웃 확인
    bool isSessionTimedOut();

    // 세션 활성화 시간 업데이트
    void updateLastActivity();

    // 세션 로그 기록 (예시)
    void logSessionActivity(const string& activity);

private:
    int sessionId;                    // 세션 ID
    int tcpSocket;                    // TCP 소켓 핸들
    int rtpPort, rtcpPort;            // RTP/RTCP 포트 정보
    int version;
    string state;                // 클라이언트 상태 (SETUP, PLAY, PAUSE 등)

    queue<string> mediaBuffer; // 미디어 프레임 큐
    chrono::time_point<chrono::system_clock> lastActivity; // 마지막 활동 시간
    const double sessionTimeout = 60.0;  // 세션 타임아웃 시간 (초)

    mutex sessionMutex;          // 세션 동기화용 뮤텍스
};

#endif //RTSP_CLIENTSESSION_H