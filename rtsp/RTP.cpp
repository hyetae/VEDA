#include "RTP.h"
#include <locale>
#include <cstring>
#include <arpa/inet.h>

RTP::RTP(uint16_t seqNum, uint32_t ssrc)
        : seqNum(seqNum), timestamp(0), ssrc(ssrc), packetCount(0), byteCount(0) {
}

// RTP 패킷 전송
unsigned char* RTP::createRTPPacket() {
    auto *packet = new unsigned char[sizeof(RTPHeader) + payloadSize];

    RTPHeader header{};
    header.version = 2;
    header.p = 0;
    header.x = 0;
    header.cc = 0;
    header.m = 0;
    header.pt = 0;  // 0 for PCMU (G.711 µ-law)
    header.seqNum = htons(seqNum);
    header.timestamp = htonl(timestamp);
    header.ssrc = htonl(ssrc);

    // 페이로드 복사
    memset(packet, 0, sizeof(packet));
    memcpy(packet, &header, sizeof(header));
    memcpy(packet + sizeof(header), payload, payloadSize);

    // 통계 업데이트
    seqNum++;
    packetCount++;
    byteCount += payloadSize;

    return packet;
}

uint32_t RTP::getTimestamp() { return timestamp; }

uint32_t RTP::getPacketCount() { return packetCount; }
