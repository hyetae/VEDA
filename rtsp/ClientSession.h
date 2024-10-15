#ifndef RTSP_CLIENTSESSION_H
#define RTSP_CLIENTSESSION_H

#include "SocketHandler.h"

#include <map>
#include <queue>
#include <mutex>
#include <chrono>
#include <string>
#include <iostream>

using namespace std;

class ClientSession {
public:
    ClientSession(int sessionId);

    int getSessionId() const;

    int getVersion() const;

    string getState() const;

    pair<int, int> getPort() const;

    void setPort(int port1, int port2);

    void setState(const string& newState);

private:
    int sessionId, version;
    int rtpPort, rtcpPort;
    string state;
    mutex mtx;
};

#endif //RTSP_CLIENTSESSION_H