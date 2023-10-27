//
//  11_fork_exec.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

/*
 ./l2_11_f ls
 ./l2_11_f ls - l
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Выполнить из программы на Си какую-либо команду Shell (cp или ls): с помощью вызовов fork-exec. Необходимые для команды данные передать через аргументы командной строки.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arg1 arg2 ...]\n", argv[0]);
        return 1;
    }

    char *command = argv[1];

    // Создаем дочерний процесс
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {  // Дочерний процесс
        // список аргументов
        printf("Child process (PID: %d) arguments:\n", getpid());
        for (int i = 1; i < argc; i++) {
            printf("Arg %d: %s\n", i-1, argv[i]);
        }

        // Выполняем команду с аргументами
        execvp(command, &argv[1]);
        
        // Если execvp завершается ошибкой, то выводим ошибку
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Родительский процесс
        // Ожидаем завершения дочернего процесса
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status %d\n", child_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
