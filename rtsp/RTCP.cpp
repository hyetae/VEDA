#include <locale>
#include <cstring>
#include <arpa/inet.h>
#include "RTCP.h"
#include "utils.h"

RTCP::RTCP(uint32_t ssrc)
    : ssrc(ssrc) {}

void RTCP::createSR(SenderReport *sr, uint32_t ssrc, uint32_t rtp_timestamp, uint32_t packet_count, uint32_t octet_count) {
    memset(sr, 0, sizeof(*sr));
    sr->version = 2;
    sr->p = 0;
    sr->rc = 0;
    sr->pt = 200;  // 200 for Sender Report
    sr->length = htons(6);  // 6 32-bit words
    sr->ssrc = htonl(ssrc);

    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    uint64_t ntp_time = ((uint64_t)(now.tv_sec + 2208988800ULL) << 32) |
                        ((uint64_t)now.tv_nsec * 0x100000000ULL / 1000000000ULL);

    sr->ntp_timestamp_msw = htonl((uint32_t)(ntp_time >> 32));
    sr->ntp_timestamp_lsw = htonl((uint32_t)(ntp_time & 0xFFFFFFFF));
    sr->rtp_timestamp = htonl(rtp_timestamp);
    sr->sender_packet_count = htonl(packet_count);
    sr->sender_octet_count = htonl(octet_count);
}

// RTCP Sender Report 전송
uint8_t* RTCP::getSenderReport() {
    SenderReport sr{};

    sr.version = 2;               // RTCP 버전
    sr.padding = 0;               // 패딩 없음
    sr.reportCount = 0;           // 리포트 블록 없음 (SR은 최소한 보고서 하나를 포함할 수 있음)
    sr.packetType = 200;          // 패킷 타입 (200은 SR)
    sr.length = htons((sizeof(sr) / 4) - 1); // 길이는 32비트 워드 단위

    auto time = utils::getTime().first;
    // 송신자 정보 설정
    sr.ssrc = htonl(ssrc);
    sr.ntpTimestampMSW = htonl((uint32_t)(time >> 32));  // 상위 32비트
    sr.ntpTimestampLSW = htonl((uint32_t)(time & 0xFFFFFFFF)); // 하위 32비트
    sr.rtpTimestamp = htonl(rtpTimestamp);
    sr.packetCount = htonl(packetCount);
    sr.octetCount = htonl(octetCount);

    memset(rtcpPacket, 0, sizeof(rtcpPacket));
    memcpy(rtcpPacket, &sr, sizeof(sr));

    return rtcpPacket;
}
