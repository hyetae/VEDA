#include <iostream>
#include <thread>

#include "ClientSession.h"
#include "RequestHandler.h"
#include "SocketHandler.h"
#include "MediaStreamHandler.h"
#define SOCK SocketHandler::getInstance()

using namespace std;

int sessionNum = 1;

int main() {

    SOCK.createTCPSocket();

    cout << "RTSP 서버가 시작되었습니다. 클라이언트 접속을 기다리는 중..." << endl;

    while (true) {
        // 클라이언트 접속을 기다림
        int clientSocket = SOCK.acceptClientConnection();
        if (clientSocket == -1) {
            cerr << "클라이언트 접속 오류" << endl;
            continue; // 오류 시 다음 클라이언트 접속 대기
        }
        cout << "클라이언트 접속 완료" << endl;

        auto mediaStreamHandler = MediaStreamHandler();
        auto requestHandler = RequestHandler(mediaStreamHandler);
        auto clientSession = ClientSession(sessionNum++);

        // 클라이언트 세션을 새로운 스레드에서 처리
        thread clientThread(&RequestHandler::handleRequest, requestHandler, clientSocket, &clientSession);
        // 스레드 비동기 처리
        clientThread.detach();
    }

    return 0;
}
