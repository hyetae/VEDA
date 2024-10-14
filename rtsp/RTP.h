#ifndef RTSP_RTP_H
#define RTSP_RTP_H

#include <cstdint>
#include <cstddef>

class RTP {
public:
    RTP(uint16_t seqNum, uint32_t ssrc);

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

    unsigned char* createRTPPacket();

    uint32_t getTimestamp();
    uint32_t getPacketCount();

private:
    size_t payloadSize;
    unsigned char* payload;

    uint16_t seqNum;
    unsigned int timestamp, ssrc, packetCount, octetCount;

    uint32_t byteCount;
};

#endif //RTSP_RTP_H
