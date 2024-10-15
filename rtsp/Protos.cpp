#include "Protos.h"
#include "utils.h"
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
Protos::Protos(uint32_t ssrc): ssrc(ssrc) {}

void Protos::createRTPPacket(unsigned short seqNum, unsigned int timestamp, unsigned char* packet, unsigned char* payload) {
    RTPHeader header;
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
    memset(packet, 0, sizeof(&packet));
    memcpy(packet, &header, sizeof(header));
    memcpy(packet + sizeof(header), payload, payloadSize);
}

void Protos::createSR(unsigned int timestamp, unsigned int packetCount, unsigned int octetCount, Protos::SenderReport* sr) {
    memset(sr, 0, sizeof(*sr));
    sr->version = 2;
    sr->p = 0;
    sr->rc = 0;
    sr->pt = 200;  // 200 for Sender Report
    sr->length = htons(6);  // 6 32-bit words
    sr->ssrc = htonl(ssrc);

    auto time = utils::getTime();
    sr->ntp_timestamp_msw = htonl((uint32_t)(time >> 32));
    sr->ntp_timestamp_lsw = htonl((uint32_t)(time & 0xFFFFFFFF));
    sr->rtp_timestamp = htonl(timestamp);
    sr->sender_packet_count = htonl(packetCount);
    sr->sender_octet_count = htonl(octetCount);
}