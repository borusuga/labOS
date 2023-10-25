//
//  3.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Написать программу, в которой процесс порождает новый и позволяет порожденному процессу завершиться. Оба процесса должны выводить свои идентификаторы (процесса, родительского процесса, группы процессов). Проверить идентификатор и статус завершения порожденного процесса. Выполнить данную программу и посмотреть ее результаты.

int main(int argc, char *argv[]) {
    pid_t child_pid, wpid;
    int status;

    printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());

    // Создаем дочерний процесс
    child_pid = fork();
    
    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }
    
    if (child_pid == 0) {
        // Код, выполняемый дочерним процессом
        printf("Child process (PID: %d, Parent PID: %d, Group ID: %d)\n",
               getpid(), getppid(), getpgrp());
        exit(52);  // Дочерний процесс завершается с кодом 52
    } else {
        // Код, выполняемый родительским процессом
        printf("Parent process waiting for child process to finish...\n");
        wpid = wait(&status);

        if (wpid == -1) {
            perror("Wait failed");
            return 1;
        }
        
        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status: %d\n", wpid, WEXITSTATUS(status));
        }
    }
    
    return 0;

}
