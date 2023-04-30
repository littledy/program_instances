#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void printID() {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    printf("pid:%u  tid:%u(0x%08x)\n", (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

static void* threadSink(void *arg) {
    printID();
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    int res = pthread_create(&tid, NULL, threadSink, NULL);     // 创建线程
    if (res != 0) {
        printf("create thread err.\n");
        exit(1);
    }

    printID();
    pthread_join(tid, NULL);  // 阻塞，等待指定线程结束

    exit(0);
}