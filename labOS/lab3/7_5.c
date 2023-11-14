//
//  7_5.c
//  labOS
//
//  Created by Alyona Borushnova on 08.11.2023.
//

// Повторить выполнение предыдущих пунктов задания, используя в порожденном процессе вместо вложенных циклов системный вызов pause. Что изменится?

// -> порождённый процесс останавливается, тогда как в 5 пункте продолжались итерации. 
// -> как и в 5 пункте - процесс прервётся


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        printf("Child process with pid: %d\n", getpid());
        pause();
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent process with pid: %d\n", getpid());
        sleep(1);
        kill(pid, SIGUSR1);
        waitpid(pid, &status, 0);
        printf("Child process with pid: %d exited with status: %d\n", pid, status);
    } else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
