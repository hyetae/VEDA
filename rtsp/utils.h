#ifndef RTSP_UTILS_H
#define RTSP_UTILS_H

#include <string>
#include <utility>
using namespace std;

class utils {
public:
    static uint64_t getTime();
    static uint32_t getRanNum(int n);
};

#endif //RTSP_UTILS_H
