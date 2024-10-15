#ifndef RTSP_SOCKETHANDLER_H
#define RTSP_SOCKETHANDLER_H

#include "Protos.h"
#include <string>
#include <arpa/inet.h>
using namespace std;

class SocketHandler {
public:
    static SocketHandler& getInstance() {
        static SocketHandler instance;
        return instance;
    }

    bool createTCPSocket();

    bool createUDPSocket(int port1, int port2);

    int acceptClientConnection();

    string receiveRTSPRequest(int clientSocket);

    void sendRTSPResponse(int clientSocket, string& response);

    void sendRTPPacket(unsigned char* rtpPacket, size_t packetSize);

    void sendSenderReport(Protos::SenderReport* senderReport, size_t srSize);

    void setUDPSocket(int port1, int port2);

    int& getTCPSocket();
    int& getRTPSocket();
    int& getRTCPSocket();

    sockaddr_in& getTCPAddr();
    sockaddr_in& getRTPAddr();
    sockaddr_in& getRTCPAddr();


private:
    SocketHandler();
    ~SocketHandler();

    int tcpPort;
    int tcpSocket;
    int rtpSocket;
    int rtcpSocket;

    sockaddr_in tcpAddr;
    sockaddr_in rtpAddr;
    sockaddr_in rtcpAddr;
};

#endif //RTSP_SOCKETHANDLER_H