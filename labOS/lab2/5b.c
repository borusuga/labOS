//
//  5.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Изменить программу п. 3 так, чтобы родительский процесс выполнялся, не ожидая завершения порожденного процесса. Что произойдет с порожденным процессом, когда он завершится? Как убить зомби?

void check_and_kill_zombie_processes(void) {
    pid_t zombie_pid;
    
    while ((zombie_pid = waitpid(-1, NULL, WNOHANG)) > 0) {
        // Kill the zombie process.
        printf("Zombie with PID: %d\n", zombie_pid);
        kill(zombie_pid, SIGCHLD);
    }
}

void child(void) {
    // Код, выполняемый дочерним процессом
    printf("Child process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());
    sleep(2);
    // Завершение дочернего
    printf("Child process terminated.\n");
    exit(0);
}

void parent(void) {
    printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());
    
    pid_t pid = fork();
    
    if (pid == 0) {
        child();
    } else {
        printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
               getpid(), getppid(), getpgrp());
        
        // Завершение родительского
        printf("Parent process terminated.\n");
    }
    
    // Ждем, пока дочерний процесс станет зомби
    sleep(5);
    
    // Удаляем зомби процесс
    int status;
    pid_t terminated_pid = waitpid(pid, &status, WNOHANG);
    if (terminated_pid > 0) {
        if (WIFEXITED(status)) {
            printf("Parent process: Zombie (PID: %d) removed. Child process (PID: %d) has terminated with exit status: %d\n", terminated_pid, pid, WEXITSTATUS(status));
        }
    } else if (terminated_pid == 0) {
        printf("Child process is still running or not exited yet.\n");
    } else if (terminated_pid == -1) {
        perror("waitpid failed");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    parent();
    
    return 0;
}
