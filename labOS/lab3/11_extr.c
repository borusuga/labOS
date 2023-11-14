//
//  11.c
//  labOS
//
//  Created by Alyona Borushnova on 08.11.2023.
//

// Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов. Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sig_flag = 0;

void signal_handler(int signum) {
    printf("Received signal: %d\n", signum);
    sig_flag = 1;
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Дочерний процесс
        sleep(5);  // Ждем некоторое время перед отправкой сигнала
        kill(getppid(), SIGUSR1);  // Отправляем сигнал родительскому процессу
        exit(0);
    } else {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());
        printf("Parent process is waiting for the signal...\n");

        sigset_t mask;
        sigemptyset(&mask);

        // Блокируем все сигналы кроме SIGUSR1
        sigaddset(&mask, SIGINT);
        sigprocmask(SIG_BLOCK, &mask, NULL);

        while (!sig_flag) {
            // Ждем сигнала
            sigsuspend(&mask);
        }

        printf("Parent process received the signal and is continuing its execution.\n");
    }

    return 0;
}
