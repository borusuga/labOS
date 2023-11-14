//
//  9.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Включить в порожденный процесс вместо системного вызова kill системный вызов alarm с перехватом сигнала. Что изменится?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

void child_disp(int sig) {
    printf("child_disp\n");
    if (sig == SIGALRM) {
        for (int i = 0; i < INT_MAX; i++) {
            printf("outer loop %d\n", i);
            for (int j = 0; j < 1000; j++)
                for (int k = 0; k < 1000; k++)
                    ;
        }
    }
    else signal(sig, SIG_DFL);
}

void child_code(void) {
    printf("signal\n");
    signal(SIGALRM, child_disp);
    printf("alarm\n");
    alarm(1);
    pause();
    exit(0);
}

int main(int argc, char *argv[]) {

    int child_pid;

    if ((child_pid = fork()) == 0) {
        child_code();
    } else {
        int code;
//        sleep(1);
//        kill(child_pid, SIGUSR1);
        wait(&code);
        printf("wait: status %d\n", code);
    }
    return 0;
}
