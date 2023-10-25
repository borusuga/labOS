//
//  4.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Изменить программу п. 3 так, чтобы родительский процесс завершился раньше порожденного. Какой процесс становится родительским для порожденного после того, как исходный родительский процесс завершился?

int main(int argc, char *argv[]) {
    
    printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());
    
    // Создаем дочерний процесс
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Этот код выполняется в порожденном (дочернем) процессе
        printf("Child process (PID: %d, Parent PID: %d, Group PID: %d) is running\n",
               getpid(), getppid(), getpgrp());
        sleep(4);
        printf("Child process (PID: %d, Parent PID: %d, Group PID: %d) is done\n",
               getpid(), getppid(), getpgrp());
    } else {
        // Этот код выполняется в родительском процессе
        printf("Parent process (PID: %d, Group PID: %d) is running\n",
               getpid(), getpgrp());
        sleep(2);
        printf("Parent process (PID: %d) is done\n", getpid());
    }

    return 0;
}
