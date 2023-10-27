//
//  4b.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

/*
 ./l2_4b
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// более структурированная

// Изменить программу п. 3 так, чтобы родительский процесс завершился раньше порожденного.

// Какой процесс становится родительским для порожденного после того, как исходный родительский процесс завершился?
// -> ppid=1

void child(void) {
    // Код, выполняемый дочерним процессом
    pid_t  parent_pid = getppid();
    
    // Ждём завершения родителя
    waitpid(parent_pid, NULL, 0);
    
    // выводим сироту
    printf("Child process is now an Orphan.\n");
    printf("Child process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());
    
    // Завершение дочернего
    printf("Child process terminated.\n");
    exit(0);
}

void parent(void) {
//    printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
//           getpid(), getppid(), getpgrp());
    
    pid_t pid = fork();
    if (pid == 0) {
        child();
    } else {
        printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
               getpid(), getppid(), getpgrp());
        // Завершение родительского
        printf("Parent process terminated.\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    parent();
    return 0;
}
