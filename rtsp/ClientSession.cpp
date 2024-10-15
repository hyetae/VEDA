#include "ClientSession.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <mutex>

#define SOCK SocketHandler::getInstance()

using namespace std;

ClientSession::ClientSession(int sessionId)
        : sessionId(sessionId), version(1), state("INIT") {
    lastActivity = chrono::system_clock::now();
}

// 세션 ID 반환
int ClientSession::getSessionId() const { return sessionId; }

// 클라이언트 버전 반환
int ClientSession::getVersion() const { return version; }

// 클라이언트 상태 반환
string ClientSession::getState() const { return state; }

pair<int, int> ClientSession::getPort() const { return {rtpPort, rtcpPort}; }

void ClientSession::setPort(int port1, int port2) {
    rtpPort = port1;
    rtcpPort = port2;

    SOCK.createUDPSocket(utils::getIP(), rtpPort, rtcpPort);
}

// 클라이언트 상태 설정 (SETUP, PLAY, PAUSE 등)
void ClientSession::setState(const string& newState) {
    lock_guard<std::mutex> lock(sessionMutex);
    state = newState;
    version++;
}