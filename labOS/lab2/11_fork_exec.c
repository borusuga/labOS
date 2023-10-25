//
//  11_fork_exec.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Выполнить из программы на Си какую-либо команду Shell (ls): с помощью вызовов fork-exec. Необходимые для команды данные передать через аргументы командной строки.

int main(int argc, char * argv[]) {
    pid_t pid;

    pid = fork();
    switch(pid) {
        case -1:
            printf("fork failed\n");
            exit(EXIT_FAILURE);
        case 0:
            execvp(argv[1], argv + 1);
        default:
            break;
    }

    exit(EXIT_SUCCESS);
}
