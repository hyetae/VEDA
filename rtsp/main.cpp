#include "utils.h"
#include "ClientSession.h"
#include "SocketHandler.h"
#include "RequestHandler.h"
#include "MediaStreamHandler.h"
#include <thread>
#include <iostream>
#define SOCK SocketHandler::getInstance()
using namespace std;

int main() {
    // TCP 소켓 생성
    SOCK.createTCPSocket();

    cout << "RTSP 서버 시작" << endl;

    while (true) {
        // 클라이언트 접속 대기
        int clientSocket = SOCK.acceptClientConnection();
        if (clientSocket == -1) {
            cerr << "클라이언트 접속 오류" << endl;
            continue; // 오류 시 다음 클라이언트 접속 대기
        }
        cout << "클라이언트 접속 완료" << endl;

        auto mediaStreamHandler = MediaStreamHandler();
        auto requestHandler = RequestHandler(mediaStreamHandler);
        auto clientSession = ClientSession((int)utils::getRanNum(16));

        // 클라이언트 세션을 새로운 스레드에서 처리
        thread clientThread(&RequestHandler::handleRequest, requestHandler, clientSocket, &clientSession);
        // 스레드 비동기 처리
        clientThread.detach();
    }

    return 0;
}
