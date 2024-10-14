#include "SocketHandler.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

SocketHandler::SocketHandler(): tcpSocket(-1), rtpSocket(-1), rtcpSocket(-1) {}

SocketHandler::~SocketHandler() {
    if (tcpSocket != -1) close(tcpSocket);
    if (rtpSocket != -1) close(rtpSocket);
    if (rtcpSocket != -1) close(rtcpSocket);
}

// TCP 소켓 초기화
int SocketHandler::initSocket(int tcpPort) {
    tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket == -1) {
        cerr << "Failed to create TCP socket\n";
        return -1;
    }

    memset(&tcpAddr, 0, sizeof(tcpAddr));
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    tcpAddr.sin_port = htons(tcpPort);

    if (::bind(tcpSocket, (struct sockaddr*)&tcpAddr, sizeof(tcpAddr)) == -1) {
        cerr << "Failed to bind TCP socket\n";
        return -1;
    }

    if (listen(tcpSocket, 10) == -1) {
        cerr << "Failed to listen on TCP socket\n";
        return -1;
    }

//    cout << "TCP socket initialized on port " << RTSP_PORT << endl;
    return tcpSocket;
}

bool SocketHandler::createUDPSocket(char* ip, int port1, int port2) {
    rtpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rtpSocket == -1) {
        cerr << "Failed to create socket: " << port1 << endl;
        return false;
    }

    rtcpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rtcpSocket == -1) {
        cerr << "Failed to create socket: " << port2 << endl;
        return false;
    }

    memset(&rtpAddr, 0, sizeof(rtpAddr));
    rtpAddr.sin_family = AF_INET;
    rtpAddr.sin_port = htons(port1);
    inet_pton(AF_INET, ip, &rtpAddr.sin_addr);

    memset(&rtcpAddr, 0, sizeof(rtcpAddr));
    rtcpAddr.sin_family = AF_INET;
    rtcpAddr.sin_port = htons(port2);
    inet_pton(AF_INET, ip, &rtcpAddr.sin_addr);

    return true;
}

// 클라이언트 접속 (blocking)
int SocketHandler::acceptClientConnection() {
    socklen_t clientAddrLen = sizeof(tcpAddr);
    int clientSocket = accept(tcpSocket, (sockaddr*)&tcpAddr, &clientAddrLen);
    if (clientSocket == -1) {
        cerr << "Failed to accept client connection\n";
        return -1;
    }

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &tcpAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    cout << "Accepted client connection from " << clientIP << endl;

    return clientSocket;
}

// RTSP 요청
string SocketHandler::receiveRTSPRequest(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int receivedBytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (receivedBytes <= 0) {
        cerr << "Failed to receive RTSP request\n";
        return "";
    }

    cout << "Received RTSP request:\n" << buffer << endl;
    return {buffer};
}

// RTSP 응답
void SocketHandler::sendRTSPResponse(int clientSocket, string& response) {
    int sentBytes = send(clientSocket, response.c_str(), response.size(), 0);
    if (sentBytes == -1) {
        cerr << "Failed to send RTSP packet\n";
        exit(1);
    }

//    cout << "Sent RTSP packet to " << clientIP << ":" << clientRTPPort << endl;
}

// RTP 응답
void SocketHandler::sendRTPPacket(unsigned char* rtpPacket) {
    int sentBytes = sendto(rtpSocket, rtpPacket, sizeof(rtpPacket), 0, (struct sockaddr*)&rtpAddr, sizeof(rtpAddr));
    if (sentBytes == -1) {
        cerr << "Failed to send RTP packet\n";
        exit(1);
    } 

//    cout << "Sent RTP packet to " << clientIP << ":" << clientRTPPort << endl;
}

// RTSP 응답
void SocketHandler::sendSenderReport(Protos::SenderReport* senderReport) {
    int sentBytes = sendto(rtcpSocket, senderReport, sizeof(senderReport), 0, (struct sockaddr*)&rtcpAddr, sizeof(rtcpAddr));
    if (sentBytes == -1) {
        cerr << "Failed to send RTCP response\n";
        exit(1);
    } 

//    cout << "Sent RTCP response:\n" << response << endl;
}
