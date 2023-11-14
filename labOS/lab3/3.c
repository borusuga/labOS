//
//  3.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Написать программу, исключающую появление зомби для завершающихся порожденных процессов.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    // Обработка сигнала SIGCHLD
    printf("SIGCHLD received by parent process\n");
    
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Обработка завершившегося процесса
        printf("Parent process reaped child process with PID %d\n", pid);
    }
    printf("SIGCHLD processed\n");
}

int main(int argc, char *argv[]) {
    // Инициализация обработчика сигнала
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);
    
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        printf("Child process with pid: %d\n", getpid());
        // Выполнение порожденного процесса
        sleep(5);
        exit(0);
    } else {
        // Родительский процесс
        printf("Parent process with pid: %d\n", getpid());
        // Ожидание завершения порожденного процесса
        sleep(5);
    }
    
    
    return 0;
}



// Установка флага SA_RESTART гарантирует, что вызов waitpid() будет перезапущен без потери данных. Это означает, что родительский процесс сможет получить информацию о завершившемся процессе, даже если вызов waitpid() был прерван сигналом.
