#include "RequestHandler.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <sstream>
#include <thread>

using namespace std;

RequestHandler::RequestHandler(SocketHandler& socketHandler, MediaStreamHandler& mediaStreamHandler)
        : socketHandler(socketHandler), mediaStreamHandler(mediaStreamHandler), isAlive(true) {}

// RTSP 요청 처리
void RequestHandler::handleRequest(int clientSocket, ClientSession* session) {
    cout << "클라이언트 스레드 생성" << endl;
    while (isAlive) {
        string request = socketHandler.receiveRTSPRequest(clientSocket);
        if (request.empty()) {
            cerr << "Invalid RTSP request received." << endl;
            return;
        }

        string method = parseMethod(request);

        // CSeq 파싱
        int cseq = parseCSeq(request);
        if (cseq == -1) {
            cerr << "CSeq parsing failed." << endl;
            return;
        }

        if (method == "OPTIONS") {
            handleOptionsRequest(clientSocket, cseq);
        } else if (method == "DESCRIBE") {
            handleDescribeRequest(clientSocket, cseq, session);
        } else if (method == "SETUP") {
            handleSetupRequest(clientSocket, cseq, session, request);
        } else if (method == "PLAY") {
            handlePlayRequest(clientSocket, cseq, session);
        } else if (method == "PAUSE") {
            handlePauseRequest(clientSocket, cseq, session);
        } else if (method == "TEARDOWN") {
            handleTeardownRequest(clientSocket, cseq, session);
        } else {
            cerr << "Unsupported RTSP method: " << method << endl;
        }
    }
}

// RTSP 요청 method 파싱
string RequestHandler::parseMethod(const string& request) {
    istringstream requestStream(request);
    string method;
    requestStream >> method;
    return method;
}

// RTSP 요청 CSeq 파싱
int RequestHandler::parseCSeq(const string& request) {
    istringstream requestStream(request);
    string line;
    while (getline(requestStream, line)) {
        if (line.find("CSeq") != string::npos) {
            istringstream lineStream(line);
            string label;
            int cseq;
            lineStream >> label >> cseq;
            return cseq;
        }
    }
    return -1; // CSeq not found
}

pair<int, int> RequestHandler::parsePorts(const string& request) {
    istringstream requestStream(request);
    string line;
    while (getline(requestStream, line)) {
        if (line.find("client_port=") != string::npos) {
            istringstream lineStream(line);
            string label;

            while (getline(lineStream, label, '=')) {
                if (label == "client_port") {
                    string portRange;
                    getline(lineStream, portRange);  // 포트 범위 읽기
                    size_t dashPos = portRange.find('-');

                    // '-'로 구분된 포트 추출
                    if (dashPos != string::npos) {
                        int rtpPort = stoi(portRange.substr(0, dashPos));      // RTP 포트
                        int rtcpPort = stoi(portRange.substr(dashPos + 1));   // RTCP 포트
                        return {rtpPort, rtcpPort};
                    }
                }
            }
        }
    }
    return {-1, -1};
}

// OPTIONS 핸들
void RequestHandler::handleOptionsRequest(int clientSocket, int cseq) {
    string response = "RTSP/1.0 200 OK\r\n"
                           "CSeq: " + to_string(cseq) + "\r\n"
                           "Public: DESCRIBE, SETUP, TEARDOWN, PLAY, PAUSE\r\n"
                           "\r\n";
    socketHandler.sendRTSPResponse(clientSocket, response);
}

// DESCRIBE 핸들 (SDP 전송)
void RequestHandler::handleDescribeRequest(int clientSocket, int cseq, ClientSession* session) {
    string ip = utils::getIP();
    string sdp = "v=0\r\n"
                      "o=- "
                      + to_string(session->getSessionId())
                      + " " + to_string(session->getVersion())
                      + " IN IP4 " + ip + "\r\n"
                      "s=Audio Stream\r\n"
                      "c=IN IP4 " + ip + "\r\n"
                      "t=" + to_string(utils::getTime()) + " 0\r\n"
                      "m=video " + to_string(session->getPort().first)
                      + " RTP/AVP 96\r\n"
                      "a=rtpmap:0 PCMU/8000\r\n";

    string response = "RTSP/1.0 200 OK\r\n"
                           "CSeq: " + to_string(cseq) + "\r\n"
                           "Content-Base: rtsp://" + ip + ":8554/\r\n"
                           "Content-Type: application/sdp\r\n"
                           "Content-Length: " + to_string(sdp.size()) + "\r\n"
                                                                             "\r\n" + sdp;
    socketHandler.sendRTSPResponse(clientSocket, response);
}

// SETUP 핸들 (RTP/RTCP 스레드 생성)
void RequestHandler::handleSetupRequest(int clientSocket, int cseq, ClientSession* session, const string& request) {
    // RTP, RTCP 포트와 주소 설정
    session->setState("SETUP");

    auto ports = parsePorts(request);
    if (ports.first < 0 || ports.second < 0) {
        cerr << "클라이언트 포트가 없습니다" << endl;
        return;
    }

    session->setPort(ports.first, ports.second);

    string response = "RTSP/1.0 200 OK\r\n"
                           "CSeq: " + to_string(cseq) + "\r\n"
                           "Transport: RTP/AVP;unicast;client_port="
                           + to_string(session->getPort().first) + "-"
                           + to_string(session->getPort().second) + "\r\n"
                           "Session: " + to_string(session->getSessionId())
                           + "\r\n"
                             "\r\n";
    socketHandler.sendRTSPResponse(clientSocket, response);

    // RTP-RTCP 스트리밍 스레드
    thread mediaStreamThread(&MediaStreamHandler::handleMediaStream, &mediaStreamHandler);
    // 스레드 비동기적으로 실행
    mediaStreamThread.detach();
}

// PLAY 핸들
void RequestHandler::handlePlayRequest(int clientSocket, int cseq, ClientSession* session) {
    session->setState("PLAY");

    string response = "RTSP/1.0 200 OK\r\n"
                           "CSeq: " + to_string(cseq) + "\r\n"
                           "Session: " + to_string(session->getSessionId())
                           + "\r\n"
                             "\r\n";
    socketHandler.sendRTSPResponse(clientSocket, response);

    // 실제 RTP 스트리밍 시작 (예시)
    mediaStreamHandler.playStreaming();
}

// PAUSE 핸들
void RequestHandler::handlePauseRequest(int clientSocket, int cseq, ClientSession* session) {
    session->setState("PAUSE");

    string response = "RTSP/1.0 200 OK\r\n"
                           "CSeq: " + to_string(cseq) + "\r\n"
                           "Session: " + to_string(session->getSessionId())
                           + "\r\n"
                             "\r\n";

    socketHandler.sendRTSPResponse(clientSocket, response);

    // RTP 스트리밍 일시 중지
    mediaStreamHandler.pauseStreaming();
    isAlive = false;
}

// TEARDOWN 핸들
void RequestHandler::handleTeardownRequest(int clientSocket, int cseq, ClientSession* session) {
    session->setState("TEARDOWN");

    string response = "RTSP/1.0 200 OK\r\n"
                           "CSeq: " + to_string(cseq) + "\r\n"
                           "Session: " + to_string(session->getSessionId())
                           + "\r\n"
                             "\r\n";

    socketHandler.sendRTSPResponse(clientSocket, response);

    // 세션 종료 로직
    mediaStreamHandler.teardown();
}
