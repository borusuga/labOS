//
//  4.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Создать длительный параллельный процесс (в порожденном процессе выполнять вложенные циклы, каждый на 100 или больше итераций, и выводить на экран номер итерации для внешнего цикла). Дождаться нормального завершения порожденного процесса. Посмотреть, какой статус будет передан в родительский процесс.

// -> status 0

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
        for (int i = 0; i < 1000; i++) {
            printf("Iteration %d\n", i);
            for (int j = 0; j < 1000; j++) {
            }
        }
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
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
