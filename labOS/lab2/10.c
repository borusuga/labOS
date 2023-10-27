//
//  10.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

/*
 ./l2_10 l2_1_for10 qwert rt
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Создать (с помощью связки fork - exec) параллельный процесс.
// Имя исполняемого файла для exec передается с помощью аргумента командной строки.
// Передать в порожденный процесс некоторую информацию через список параметров (список аргументов в функции main).
// Каждый процесс (и родительский, и порожденный) должен вывести на экран список переданных ему аргументов и свое окружение.

extern char** environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <executable> [arg1 arg2 ...]\n", argv[0]);
        return 1;
    }

    char *executable = argv[1];

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process (PID: %d) arguments:\n", getpid());
        for (int i = 1; i < argc; i++) {
            printf("Arg %d: %s\n", i-1, argv[i]);
        }

        // Execute the specified program with the provided arguments
        execv(executable, &argv[1]);
        
        perror("Exec failed");

        
        exit(1);
    } else {
        // Parent process
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status %d\n", child_pid, WEXITSTATUS(status));
        }

        printf("Parent process (PID: %d) arguments:\n", getpid());
        for (int i = 0; i < argc; i++) {
            printf("Arg %d: %s\n", i, argv[i]);
        }

        char **env = environ;
        printf("Parent process environment:\n");
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
    }

    return 0;
}

// нельзя совмещать потому что возникает противоречие с какого окружении брать перемену из старого или нового
