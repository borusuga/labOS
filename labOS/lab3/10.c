//
//  10_1.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Написать программу, иллюстрирующую способ блокирования дополнительных сигналов на время работы обработчика сигнала.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("Received signal: %d\n", signum);
//    sleep(3);
    for (int i = 1; i <= 100000; ++i)
    for (int j = 0; j < 100000; ++j);
    printf("Signal processed: %d\n", signum);
}

int main(int argc, char *argv[]) {
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    int child_status;
    // Создаем дочерний процесс
    pid_t pid = fork();

    if (!pid) {
        // Дочерний процесс
        // Устанавливаем обработчик сигнала SIGUSR1
        printf("Child process (PID: %d) is running...\n", getpid());
        signal(SIGUSR1, signal_handler);
        signal(SIGUSR2, signal_handler);
        signal(SIGQUIT, SIG_IGN);
        
        for (int i = 1; i <= 40; ++i) {
            printf("Дочерний процесс: Итерация i: %d\n", i);
            for (int j = 0; j < 100000000; ++j);
        }
        
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());
        // Ожидаем некоторое время, чтобы дать дочернему процессу запуститься
        sleep(1);
        // Посылаем сигналы в дочерний процесс
        signal(SIGQUIT, SIG_IGN);
        sleep(1);
        printf ("Посылем сигнал SIGUSR1\n");
        kill(pid, SIGUSR1);
        printf ("Посылем сигнал SIGUSR1\n");
        kill(pid, SIGUSR1);
        printf ("Посылем сигнал SIGUSR2\n");
        kill(pid, SIGUSR2);
        printf ("Посылем сигнал SIGUSR2\n");
        kill(pid, SIGUSR2);
        printf ("Посылем сигнал SIGUSR1\n");
        kill(pid, SIGUSR1);
        printf ("Посылем сигнал SIGUSR2\n");
        kill(pid, SIGUSR2);
        // Ожидаем завершения дочернего процесса
        pid = waitpid(pid, &child_status, 0);

        if (WIFEXITED(child_status)) {
            printf("Child process terminated normally with status %d.\n", WEXITSTATUS(child_status));
        } else {
            printf("Child process terminated abnormally.\n");
        }
    } else if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
