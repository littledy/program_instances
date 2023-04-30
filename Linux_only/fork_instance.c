// #include "include/apue.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

int globalvar = 6;
char buf[] = "a write to stdout\n";

int main() {
    int var;
    pid_t pid;

    var = 88;
    /*
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
        // err_sys("write error");
        printf("write error");
    }
    */
    printf("before fork\n");

    if ((pid = fork()) < 0) {
        // err_sys("fork error");
        printf("fork error");
    } else if (pid == 0) {
        globalvar++;
        var++;
    } else {
        sleep(2);
    }

    printf("pid = %ld, globvar = %d, var = %d\n", (long)getpid(), globalvar, var);
    // exit(0);
    return 0;
}