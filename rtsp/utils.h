#ifndef RTSP_UTILS_H
#define RTSP_UTILS_H

#include <utility>
#include <string>

using namespace std;

class utils {
public:
    // 현재 시간
    static uint64_t getTime();
    static uint16_t genSeqNum();
    static uint32_t genSSRC();
    static string getIP();
};

#endif //RTSP_UTILS_H
