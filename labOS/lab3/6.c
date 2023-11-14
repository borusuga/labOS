//
//  6.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Повторить выполнение п. 5 задания, изменив сигнал, посылаемый в порожденный процесс. Что изменится?

// -> 31

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
        
        for (int i = 0; i < 1000; i++) {
            printf("Iteration %d\n", i);
            for (int j = 0; j < 1000; j++) {
                for (int k = 0; k < 1000; k++);
            }
        }
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent process with pid: %d\n", getpid());
        sleep(1);
        kill(pid, SIGUSR2);
        waitpid(pid, &status, 0);
        printf("Child process with pid: %d exited with status: %d\n", pid, status);
    } else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
