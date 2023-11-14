//
//  7.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Повторить выполнение предыдущих пунктов задания, используя в порожденном процессе вместо вложенных циклов системный вызов pause. Что изменится? Как завершить процесс в случае выполнения с pause п. 4?

// -> порождённый процесс останавливается, тогда как в 4 пункте продолжались итерации. Тут он завершается по сигналу, а в 4 по завершении итераций мы бы вышли из обработчика

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int child_status;

    pid = fork();

    if (pid == 0) {
        // Дочерний процесс
        printf("Child process (PID: %d) is running...\n", getpid());
        pause(); // kill -SIGINT/SIGKILL/SIGUSR1 <PID>
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());
        printf("Parent process waiting for child to finish...\n");
        pid = waitpid(pid, &child_status, 0);

        if (WIFEXITED(child_status)) {
            printf("Child process terminated normally with status %d.\n", WEXITSTATUS(child_status));
        } else {
            printf("Child process terminated abnormally.\n");
        }
    } else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
