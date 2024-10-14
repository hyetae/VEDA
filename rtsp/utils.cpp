#include <chrono>
#include <random>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "utils.h"

using namespace std;

// 현재 시간
uint64_t utils::getTime() {
//    time_t now = time(nullptr); // 현재 Unix 시간
//    const unsigned long long SECONDS_FROM_1900_TO_1970 = 2208988800ULL;
//    return static_cast<unsigned long long>(now) + SECONDS_FROM_1900_TO_1970;

    auto now = chrono::system_clock::now();
    auto msSinceEpoch = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    uint32_t ntpSeconds = (msSinceEpoch / 1000) + 2208988800U; // 1970 to 1900
    uint32_t ntpFraction = (msSinceEpoch % 1000) * 4294967;
    uint64_t ntpTime = ((uint64_t)ntpSeconds << 32) | ntpFraction;
    return ntpTime;
}

uint16_t utils::genSeqNum() {
    srand((unsigned int)time(NULL));
    return rand() % 65535;
}

uint32_t utils::genSSRC() {
    // 랜덤 숫자를 생성하는 엔진 (Mersenne Twister 엔진 사용)
    random_device rd; // 랜덤 시드 생성
    mt19937 generator(rd()); // 시드를 기반으로 난수 생성 엔진 초기화
    uniform_int_distribution<uint32_t> distribution(0, 0xFFFFFFFF); // 0에서 2^32-1 범위의 난수 생성

    // 32비트 랜덤 SSRC 값 생성
    return distribution(generator);
}

string utils::getIP() {
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;

    // Get the hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1) {
        perror("gethostname");
        return "";
    }

    // Get host information
    host_entry = gethostbyname(hostbuffer);
    if (host_entry == nullptr) {
        perror("gethostbyname");
        return "";
    }

    // Convert the host's binary address into text form
    IPbuffer = inet_ntoa(*((struct in_addr *) host_entry->h_addr_list[0]));

    return std::string(IPbuffer);
}