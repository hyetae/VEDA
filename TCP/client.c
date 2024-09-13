#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <signal.h>

#define ANSI_COLOR_ORANGE "\033[38;5;214m"
#define ANSI_COLOR_RESET "\033[0m"

const int TCP_PORT = 5100;
const int MAX_ID = 32;
const int MAX_CONTENT = 1024;

// 패딩 무시 추가
typedef struct {
    char id[MAX_ID];
    char content[MAX_CONTENT];
} Message;

int ssock;
int pipeFd[2];  // 자식과 부모가 통신할 pipe

void printAsciiArt() {
    const char *chatstream[] = {
            "",
            " _____  _             _     _____  _",
            "/  __ \\| |           | |   /  ___|| |",
            "| /  \\/| |__    __ _ | |_  \\ `--. | |_  _ __   ___   __ _  _ __ ___",
            "| |    | '_ \\  / _` || __|  `--. \\| __|| '__| / _ \\ / _` || '_ ` _ \\",
            "| \\__/\\| | | || (_| || |_  /\\__/ /| |_ | |   |  __/| (_| || | | | | |",
            " \\____/|_| |_| \\__,_| \\__| \\____/  \\__||_|    \\___| \\__,_||_| |_| |_|",
            ""
    };

    printf("⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢\n");
    printf("﹉﹉﹉﹉﹉୨୧﹉﹉﹉﹉﹉୨୧﹉﹉﹉﹉﹉୨୧﹉﹉﹉﹉﹉୨୧﹉﹉﹉﹉﹉୨୧﹉﹉﹉﹉﹉୨୧﹉﹉﹉﹉\n");

    for (int i = 0; i < 8; i++)
        printf(ANSI_COLOR_ORANGE "%s" ANSI_COLOR_RESET "\n", chatstream[i]);

    printf("\n﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍\n");
}

void nonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);  // 현재 플래그 읽기
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);  // O_NONBLOCK 플래그 추가하여 비동기 모드로 설정
}

void sigHandler(int sig) {
    Message msg;
    memset(&msg, 0, sizeof(msg));
    if (read(pipeFd[0], &msg, sizeof(msg)) <= 0) {
        perror("[sigHandler]: read()");
        exit(1);
    }

    char newmsg[MAX_CONTENT] = "|";
    strcat(newmsg, msg.content);
    printf("%80s\n%79s|\n", msg.id, newmsg);
}

void recvHandler() {
    Message msg;
    while (1) {
        memset(&msg, 0, sizeof(msg));
        if (read(ssock, &msg, sizeof(msg)) > 0) {
            // 서버에서 수신한 메시지를 부모 프로세스에 전달
            if (write(pipeFd[1], &msg, sizeof(msg)) <= 0) {
                perror("[recvHandler]: write()");
                exit(1);
            }
            kill(getppid(), SIGUSR1);  // 부모에게 SIGUSR1 신호를 보냄
        } else {
            perror("[recvHandler]: read()");
            exit(1);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s IP_ADDRESS\n", argv[0]);
        return -1;
    }

    system("clear");

    struct sockaddr_in saddr;
    Message msg;
    char id[MAX_ID];

    // 서버에 연결할 소켓 생성
    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[main]: socket()");
        return -1;
    }

//    nonBlocking(ssock);

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(saddr.sin_addr.s_addr));
    saddr.sin_port = htons(TCP_PORT);

    // 서버에 연결
    if (connect(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("[main]: connect()");
        return -1;
    }

//    printf("Connected to server!\n");

    printAsciiArt();

    // 사용자 ID 입력
    printf("\n\t\t\tLet me know your nickname!\n\n\t\t\t>> ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;  // 개행 문자 제거
    printf("\n\t\t\tWelcom to Chat Stream, %s!\n", id);
    printf("\t\t\tIf you wanna quit, press \"q\"!\n");
    printf("\t\t\tIf you wanna clean, press \"c\"!\n");
    printf("\t\t\tIf you need help, press \"h\"!\n");
    printf("\n﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍\n");
    printf("⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣\n");
    sleep(4);
    system("clear");
    printAsciiArt();

    // pipe 생성
    if (pipe(pipeFd) < 0) {
        perror("[main]: pipe()");
        return -1;
    }

    // 신호 핸들러 설정
    signal(SIGUSR1, sigHandler);

    // 메시지 수신을 위한 자식 프로세스 생성
    if (fork() == 0) {
        recvHandler();
        exit(0);
    }

    // 부모 프로세스는 사용자 입력을 서버로 전송
    while (1) {
        memset(&msg, 0, sizeof(msg));
        strcpy(msg.id, id);

        fgets(msg.content, MAX_CONTENT, stdin);
        msg.content[strcspn(msg.content, "\n")] = 0;  // 개행 문자 제거

        if (write(ssock, &msg, sizeof(msg)) <= 0) {
            perror("[main]: write()");
            return -1;
        }

        if (!strcmp(msg.content, "q"))
            break;

        if (!strcmp(msg.content, "c")) {
            system("clear");
            printAsciiArt();
        }

        if (!strcmp(msg.content, "h")) {
            printf(ANSI_COLOR_ORANGE "----------HELP----------\n");
            printf("   1. \"q\" for quit\n");
            printf("   2. \"c\" for clear\n");
            printf("   3. \"h\" for help\n");
            printf("------------------------\n" ANSI_COLOR_RESET);
        }
    }

    close(ssock);
    return 0;
}
