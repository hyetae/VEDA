#include <chrono>
#include <random>
#include "utils.h"

using namespace std;

// 현재 시간
uint64_t utils::getTime() {
//    time_t now = time(nullptr); // 현재 Unix 시간
//    const unsigned long long SECONDS_FROM_1900_TO_1970 = 2208988800ULL;
//    return static_cast<unsigned long long>(now) + SECONDS_FROM_1900_TO_1970;

    auto now = chrono::system_clock::now();
    auto ms_since_epoch = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    uint32_t ntpSeconds = (ms_since_epoch / 1000) + 2208988800U; // 1970 to 1900
    uint32_t ntpFraction = (ms_since_epoch % 1000) * 4294967;

    uint64_t ntp_time = ((uint64_t)ntp_seconds << 32) | ntp_fraction;

    return ntp_time;
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