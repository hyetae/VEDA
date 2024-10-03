#include <iostream>
#include "vd_main.h"

struct main_data_struct {
    sever_sock;
    log_handle;
    conf_data;
    client_session_hash;
    ...
};

void init();
void main_loop();
void destroy();

int main() {
    init();
    main_loop();
    destroy();
    return 0;
}

void init() {
    // main_data_struct 생성
    // 초기화
}

void main_loop() {
    while (1) {
        // 서버 소켓에서 클라이언트 접속을  기다림
        if (1) { // 클라이언트 접속
            // 클라이언트 세션 생성;
            // 클라이언트 세선의 main thread 시작
            vd_main::main_thread_run();
        }
    }
}

void destroy() {
    // main_data_struct 삭제
    // 정리
}