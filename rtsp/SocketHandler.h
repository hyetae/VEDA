#ifndef RTSP_SOCKETHANDLER_H
#define RTSP_SOCKETHANDLER_H

#include "Protos.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <vector>

using namespace std;

class SocketHandler {
public:
    SocketHandler();
    ~SocketHandler();

    // TCP 소켓 초기화
    int initSocket(int tcpPort);

    bool createUDPSocket(char* ip, int port1, int port2);

    // 클라이언트 접속 (blocking)
    int acceptClientConnection();

    // RTSP 요청
    string receiveRTSPRequest(int clientSocket);

    // RTSP 응답
    void sendRTSPResponse(int clientSocket, string& response);

    // RTP 응답
    void sendRTPPacket(unsigned char* rtpPacket);

    // RTCP 응답
    void sendSenderReport(Protos::SenderReport* senderReport);

private:

    int tcpSocket;  // TCP socket for RTSP communication
    int rtpSocket;  // UDP socket for RTP packets
    int rtcpSocket; // UDP socket for RTCP packets

    sockaddr_in tcpAddr;
    sockaddr_in rtpAddr;
    sockaddr_in rtcpAddr;
};

#endif //RTSP_SOCKETHANDLER_H