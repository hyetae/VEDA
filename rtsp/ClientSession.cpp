#include "ClientSession.h"
#include <mutex>
#include <string>
#define SOCK SocketHandler::getInstance()
using namespace std;

ClientSession::ClientSession(int sessionId)
        : sessionId(sessionId), version(sessionId), state("INIT") {}

int ClientSession::getSessionId() const { return sessionId; }

int ClientSession::getVersion() const { return version; }

string ClientSession::getState() const { return state; }

pair<int, int> ClientSession::getPort() const { return {rtpPort, rtcpPort}; }

void ClientSession::setPort(int port1, int port2) {
    rtpPort = port1;
    rtcpPort = port2;

    SOCK.createUDPSocket(rtpPort, rtcpPort);
}

void ClientSession::setState(const string& newState) {
    lock_guard<mutex> lock(mtx);
    state = newState;
    version++;
}