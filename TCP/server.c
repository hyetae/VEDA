#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/syslog.h>

const int TCP_PORT = 5100;
const int MAX_ID = 32;
const int MAX_CONTENT = 1024;
const int MAX_CLIENTS = 50;

typedef struct {
    char id[MAX_ID];
    char content[MAX_CONTENT];
} Message;

typedef struct {
    char id[MAX_ID];
    char pw[MAX_ID];
} User;

pid_t pids[MAX_CLIENTS];
int pipes1[MAX_CLIENTS][2];
int pipes2[MAX_CLIENTS][2];
int clients[MAX_CLIENTS]; // socket
int clientsNum;
int idx;

void nonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}

int beDaemon(char *cmd) {
    struct sigaction sa;
    struct rlimit rl;
    pid_t pid;
    int fd0, fd1, fd2;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        perror("getrlimit()");
        return -1;
    }

    if ((pid = fork()) < 0) {
        perror("fork()");
        return -1;
    } else if (pid != 0) return -1;

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        perror("sigaction(): Can't ignore SIGHUP");
        return -1;
    }

    if ((pid = fork()) < 0) {
        perror("fork()");
        return -1;
    } else if (pid != 0) return -1;

    // 루트 디렉토리로 변경
    if (chdir("/") < 0) {
        perror("chdir()");
        return -1;
    }

    // 파일 디스크립터 닫기
    if (rl.rlim_max == RLIM_INFINITY) rl.rlim_max = 1024;
    for (int i = 0; i < rl.rlim_max; i++)
        close(i);

    // 표준 입출력 연결을 /dev/null로 리다이렉트
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(EXIT_FAILURE);
    }

    syslog(LOG_INFO, "Daemon process started");
    return 0;
}

void sig1Handler(int sig, siginfo_t *info) {
//    printf("sig1Handler()\n");

    Message msg;
    pid_t whoSend = info->si_pid;

    memset(msg.id, 0, sizeof(msg.id));
    memset(msg.content, 0, sizeof(msg.content));

    int senderIdx = -1;
    for (int i = 0; i < clientsNum; i++) {
        if (pids[i] == whoSend) {
            senderIdx = i;
            break;
        }
    }

    if (senderIdx == -1) {
//        printf("[sig1Handler]: Invalid sender pid.\n");
        return;
    }

    if (read(pipes1[senderIdx][0], &msg, sizeof(msg)) <= 0)
        perror("[sig1Handler]: read()");

//    printf("[daemon] %s: %s\n", msg.id, msg.content);

    for (int j = 0; j < clientsNum; j++) {
        if (pids[j] != whoSend) {
            if (write(pipes2[j][1], &msg, sizeof(msg)) <= 0)
                perror("[sig1Handler]: write()");
            kill(pids[j], SIGUSR2);
        }
    }
}

void sig2Handler(int sig) {
//    printf("sig2Handler()\n");

    Message msg;
    memset(msg.id, 0, sizeof(msg.id));
    memset(msg.content, 0, sizeof(msg.content));

    if(read(pipes2[idx][0], &msg, sizeof(msg)) <= 0)
        perror("[sig2Handler]: read()");

//    printf("[parent] %s: %s\n", msg.id, msg.content);
    if(write(clients[idx], &msg, sizeof(msg)) <= 0)
        perror("[sig2Handler]: write()");
}

void clientHandler(int csock) {
    Message msg;
    idx = clientsNum;
    while (1) {
        if (read(csock, &msg, sizeof(msg)) <= 0)
            perror("[clientHandlr]: read()");

//        printf("[child] %s: %s\n", msg.id, msg.content);

        if (!strncmp(msg.content, "q", 1))
            break;

        if (write(pipes1[clientsNum][1], &msg, sizeof(msg)) < 0)
            perror("[clientHandlr]: write()");

        kill(getppid(), SIGUSR1);
    }
}

int main(int argc, char **argv) {

    if(beDaemon(argv[0]) < 0)
        return -1;

    int ssock, csock;
    struct sockaddr_in saddr, caddr;
    socklen_t clen = sizeof(caddr);
    pid_t pid;
    char buffer[BUFSIZ];

    struct sigaction sa;
    sa.sa_sigaction = (void (*)(int, struct __siginfo *, void *)) sig1Handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    signal(SIGUSR2, sig2Handler);

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("[main]: socket()");
        return -1;
    }

//    nonBlocking(ssock);

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(TCP_PORT);

    if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
        perror("[main]: bind()");
        return -1;
    }

    if (listen(ssock, MAX_CLIENTS) < 0){
        perror("[main]: listen()");
        return -1;
    }

//    printf("Server Start!\n");

    clen = sizeof(caddr);
    while (clientsNum < MAX_CLIENTS) {
        csock = accept(ssock, (struct sockaddr *) &caddr, &clen);
        if (csock < 0) {
            perror("[main]: accept()");
            continue;
        }

//        nonBlocking(csock);

        clients[clientsNum] = csock;
        inet_ntop(AF_INET, &caddr.sin_addr, buffer, BUFSIZ);

//        printf("New client connected!\n");

        if(pipe(pipes1[clientsNum]) < 0){
            perror("[main]: pipe()");
            return -1;
        }

        if(pipe(pipes2[clientsNum]) < 0){
            perror("[main]: pipe()");
            return -1;
        }

        if ((pid = fork()) < 0){
            perror("[main]: fork()");
            return -1;
        } else if (!pid) {
            clientHandler(csock);
            close(csock);
            exit(0);
        } else {
            pids[clientsNum++] = pid;
        }
    }

    close(ssock);
    return 0;
}
