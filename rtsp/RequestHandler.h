#ifndef RTSP_REQUESTHANDLER_H
#define RTSP_REQUESTHANDLER_H
#include <string>
#include "SocketHandler.h"
#include "ClientSession.h"
#include "MediaStreamHandler.h"

class RequestHandler {
public:
    RequestHandler(MediaStreamHandler& mediaStreamHandler);

    // RTSP 요청 처리
    void handleRequest(int clientSocket, ClientSession* session);

private:
    MediaStreamHandler& mediaStreamHandler;
    bool isAlive;

    // RTSP 요청 method 파싱
    string parseMethod(const string& request);

    // RTSP 요청 CSeq 파싱
    int parseCSeq(const string& request);

    pair<int, int> parsePorts(const string& request);

    // DESCRIBE 핸들 (SDP 전송)
    void handleOptionsRequest(int clientSocket, int cseq);

    // SETUP 핸들 (RTP/RTCP 스레드 생성)
    void handleDescribeRequest(int clientSocket, int cseq, ClientSession* session);

    // PLAY 핸들
    void handleSetupRequest(int clientSocket, int cseq, ClientSession* session, const string& request);

    // Handle PLAY request (starts streaming the media)
    void handlePlayRequest(int clientSocket, int cseq, ClientSession* session);

    // Handle PAUSE request (pauses the media stream)
    void handlePauseRequest(int clientSocket, int cseq, ClientSession* session);

    // Handle TEARDOWN request (terminates the session)
    void handleTeardownRequest(int clientSocket, int cseq, ClientSession* session);
};

#endif //RTSP_REQUESTHANDLER_H