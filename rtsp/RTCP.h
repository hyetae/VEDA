#ifndef RTSP_RTCP_H
#define RTSP_RTCP_H

#include <cstdint>

class RTCP {
public:
    RTCP(uint32_t ssrc);

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

    void createSR(SenderReport *sr, uint32_t ssrc, uint32_t rtp_timestamp, uint32_t packet_count, uint32_t octet_count);
    uint8_t* getSenderReport();

private:
    uint8_t rtcpPacket[1500]{}; // RTCP SR 패킷

    uint32_t ssrc;
    uint32_t rtpTimestamp;
    uint32_t packetCount;
    uint32_t octetCount;
};


#endif //RTSP_RTCP_H
