#include <iostream>
#include <thread>

#include "ClientSession.h"
#include "RequestHandler.h"
#include "SocketHandler.h"
#include "MediaStreamHandler.h"

#define TCP_PORT 8554
#define RTP_PORT 5004
#define RTCP_PORT 5005
#define DEST_IP "192.168.2.2"

using namespace std;

int sessionNum = 1;

int main() {

    auto socketHandler = SocketHandler();

    // SocketHandler 초기화
    int tcpSocket = socketHandler.initSocket(DEST_IP, TCP_PORT, RTP_PORT, RTCP_PORT);
    if (tcpSocket < 0) {
        cerr << "RTSP 서버 소켓 초기화 실패" << endl;
        return -1;
    }

    cout << "RTSP 서버가 시작되었습니다. 클라이언트 접속을 기다리는 중..." << endl;

    while (true) {
        // 클라이언트 접속을 기다림
        int clientSocket = socketHandler.acceptClientConnection();
        if (clientSocket == -1) {
            cerr << "클라이언트 접속 오류" << endl;
            continue; // 오류 시 다음 클라이언트 접속 대기
        }
        cout << "클라이언트 접속 완료" << endl;

//        auto sessionHandler = new SessionHandler();
        auto mediaStreamHandler = MediaStreamHandler(socketHandler);
        auto requestHandler = RequestHandler(socketHandler, mediaStreamHandler);
        auto clientSession = ClientSession(sessionNum++, tcpSocket, RTP_PORT, RTCP_PORT);

        // 클라이언트 세션을 새로운 스레드에서 처리
        thread clientThread(&RequestHandler::handleRequest, requestHandler, clientSocket, &clientSession);
        // 스레드 비동기 처리
        clientThread.detach();
    }

    return 0;
}
