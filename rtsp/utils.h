#ifndef RTSP_UTILS_H
#define RTSP_UTILS_H

#include <utility>
#include <string>

using namespace std;

class utils {
public:
    // 현재 시간
    static uint64_t getTime();
    static uint32_t genRanNum(int n);
    static char* getIP();
};

#endif //RTSP_UTILS_H
