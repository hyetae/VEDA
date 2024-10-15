#include "SocketHandler.h"
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

SocketHandler::SocketHandler(): tcpPort(8554), tcpSocket(-1), rtpSocket(-1), rtcpSocket(-1) {}

SocketHandler::~SocketHandler() {
    if (tcpSocket != -1) close(tcpSocket);
    if (rtpSocket != -1) close(rtpSocket);
    if (rtcpSocket != -1) close(rtcpSocket);
}

bool SocketHandler::createTCPSocket() {
    tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket == -1) {
        cerr << "tcp 소켓 생성 실패" << endl;
        return false;
    }

    memset(&tcpAddr, 0, sizeof(tcpAddr));
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    tcpAddr.sin_port = htons(tcpPort);

    if (::bind(tcpSocket, (struct sockaddr*)&tcpAddr, sizeof(tcpAddr)) == -1) {
        cerr << "tcp 소켓 바인딩 실패" << endl;
        return false;
    }

    if (listen(tcpSocket, 10) == -1) {
        cerr << "tcp 소켓 리스닝 실패" << endl;
        return false;
    }

    return true;
}

bool SocketHandler::createUDPSocket(int port1, int port2) {
    rtpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rtpSocket == -1) {
        cerr << "rtp 소켓 생성 실패" << endl;
        return false;
    }

    rtcpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (rtcpSocket == -1) {
        cerr << "rtcp 소켓 생성 실패" << endl;
        return false;
    }

    memset(&rtpAddr, 0, sizeof(rtpAddr));
    rtpAddr.sin_family = AF_INET;
    rtpAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    rtpAddr.sin_port = htons(port1);

    memset(&rtcpAddr, 0, sizeof(rtcpAddr));
    rtcpAddr.sin_family = AF_INET;
    rtcpAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    rtcpAddr.sin_port = htons(port2);

    return true;
}

int SocketHandler::acceptClientConnection() {
    socklen_t clientAddrLen = sizeof(tcpAddr);
    int clientSocket = accept(tcpSocket, (sockaddr*)&tcpAddr, &clientAddrLen);
    if (clientSocket == -1) {
        cerr << "클라이언트 접속 실패" << endl;
        return -1;
    }

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &tcpAddr.sin_addr, clientIP, INET_ADDRSTRLEN);

    return clientSocket;
}

string SocketHandler::receiveRTSPRequest(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int receivedBytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (receivedBytes <= 0) {
        cerr << "rtsp 요청 받기 실패" << endl;
        return nullptr;
    }

    cout << "rtsp 요청:\n" << buffer << endl;
    return {buffer};
}

void SocketHandler::sendRTSPResponse(int clientSocket, string& response) {
    int sentBytes = send(clientSocket, response.c_str(), response.size(), 0);
    if (sentBytes == -1) {
        cerr << "rtsp 응답 실패" << endl;
        exit(1);
    }
}

void SocketHandler::sendRTPPacket(unsigned char* rtpPacket, size_t packetSize) {
    int sentBytes = sendto(rtpSocket, rtpPacket, packetSize, 0, (struct sockaddr*)&rtpAddr, sizeof(rtpAddr));
    if (sentBytes == -1) {
        cerr << "rtp 응답 실패" << endl;
        exit(1);
    }
}

void SocketHandler::sendSenderReport(Protos::SenderReport* senderReport, size_t srSize) {
    int sentBytes = sendto(rtcpSocket, senderReport, srSize, 0, (struct sockaddr*)&rtcpAddr, sizeof(rtcpAddr));
    if (sentBytes == -1) {
        cerr << "rtcp 전송 실패" << endl;
        exit(1);
    }
}

int& SocketHandler::getTCPSocket() { return tcpSocket; }
int& SocketHandler::getRTPSocket() { return rtpSocket; }
int& SocketHandler::getRTCPSocket() { return rtcpSocket; }

sockaddr_in& SocketHandler::getTCPAddr() { return tcpAddr; }
sockaddr_in& SocketHandler::getRTPAddr() { return rtpAddr; }
sockaddr_in& SocketHandler::getRTCPAddr() { return rtcpAddr; }
