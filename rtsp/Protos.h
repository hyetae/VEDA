#ifndef RTSP_PROTOS_H
#define RTSP_PROTOS_H

#include <cstdint>
#include <cstddef>

class Protos {
public:
    Protos(uint32_t ssrc);

    struct RTPHeader {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint8_t cc:4;
        uint8_t x:1;
        uint8_t p:1;
        uint8_t version:2;
        uint8_t pt:7;
        uint8_t m:1;
#elif __BYTE_ORDER == __BIG_ENDIAN
        uint8_t version:2;
    uint8_t p:1;
    uint8_t x:1;
    uint8_t cc:4;
    uint8_t m:1;
    uint8_t pt:7;
#else
#error "Please fix <bits/endian.h>"
#endif
        uint16_t seqNum;
        uint32_t timestamp;
        uint32_t ssrc;
    } __attribute__((packed));

    struct SenderReport {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint8_t rc:5;
        uint8_t p:1;
        uint8_t version:2;
#elif __BYTE_ORDER == __BIG_ENDIAN
        uint8_t version:2;
    uint8_t p:1;
    uint8_t rc:5;
#else
#error "Please fix <bits/endian.h>"
#endif
        uint8_t pt;
        uint16_t length;
        uint32_t ssrc;
        uint32_t ntpTimestampMsw;
        uint32_t ntpTimestampLsw;
        uint32_t rtpTimestamp;
        uint32_t senderPacketCount;
        uint32_t senderOctetCount;
    } __attribute__((packed));

    void createRTPPacket(unsigned short seqNum, unsigned int timestamp, unsigned char* packet, unsigned char* payload);
    void createSR(unsigned int timestamp, unsigned int packetCount, unsigned int octetCount, SenderReport* sr);

private:
    size_t payloadSize;
    unsigned int ssrc;
    uint32_t byteCount;
};

#endif //RTSP_PROTOS_H
