#include "utils.h"
#include <chrono>
#include <random>
#include <netdb.h>
#include <iomanip>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

uint64_t utils::getTime() {
    auto now = chrono::system_clock::now();
    auto msSinceEpoch = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    uint32_t ntpSeconds = (msSinceEpoch / 1000) + 2208988800U; // 1970 to 1900
    uint32_t ntpFraction = (msSinceEpoch % 1000) * 4294967;
    uint64_t ntpTime = ((uint64_t)ntpSeconds << 32) | ntpFraction;
    return ntpTime;
}

uint32_t utils::getRanNum(int n) {
    random_device rd; // 랜덤 시드 생성
    mt19937 generator(rd()); // 시드를 기반으로 난수 생성 엔진 초기화
    if (n == 32) {
        uniform_int_distribution<uint32_t> distribution(1, 0xFFFFFFFF); // 0~2^32-1 난수 생성
        return distribution(generator);
    } else if (n == 16) {
        uniform_int_distribution<uint32_t> distribution(1, 65535);
        return distribution(generator);
    }
    return 0;
}

char* utils::getIP() {
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

    return IPbuffer;
}