#include <stdio.h>
#include <pthread.h>

// 编译时加上 -lpthread 库

void *do_loop(void *data) {
    int i;
    int j;
    int me = *((int *)data);

    for (i = 0; i < 1000; ++i) {
        for (j = 0; j < 5000000; ++j) {     // for delay
            ;
        }
        printf("'%d' - Got '%d'\n", me , i);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int thr_id;
    pthread_t p_thread;
    int a = 1;
    int b = 2;

    thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)&a);
    do_loop((void*)&b);

    return 0;
}