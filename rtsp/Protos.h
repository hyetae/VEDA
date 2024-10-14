#ifndef RTSP_PROTOS_H
#define RTSP_PROTOS_H

#include <cstdint>
#include <cstddef>

class Protos {
public:
    Protos(uint16_t seqNum, uint32_t ssrc);

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
        uint32_t ntp_timestamp_msw;
        uint32_t ntp_timestamp_lsw;
        uint32_t rtp_timestamp;
        uint32_t sender_packet_count;
        uint32_t sender_octet_count;
    } __attribute__((packed));

    void createRTPPacket(unsigned char* packet, unsigned char* payload);
    void createSR(SenderReport* sr);
    unsigned int getPacketCount();

private:
    size_t payloadSize;

    uint16_t seqNum;
    unsigned int timestamp, ssrc, packetCount, octetCount;

    uint32_t byteCount;
};

#endif //RTSP_PROTOS_H