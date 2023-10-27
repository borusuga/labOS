//
//  11_sys.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

/*
 ./l2_11_sys ls
 ./l2_11_sys ls -l
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//с помощью библиотечной функции system.

int main(int argc, char * argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arg1 arg2 ...]\n", argv[0]);
        return 1;
    }
    
    // Сборка команды и ее аргументов в строку
    char command[4096] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }
    
    int status = system(command);

    if (WIFEXITED(status)) {
        printf("Command exited with status %d\n", WEXITSTATUS(status));
    } else {
        printf("Command didn't exit normally\n");
    }
    
    exit(EXIT_SUCCESS);
}
