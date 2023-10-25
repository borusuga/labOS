//
//  2.c
//  labOS
//
//  Created by Alyona Borushnova on 24.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Кто выполняется первым после fork: отец или сын? Написать программу, которую можно использовать для проверки данной ситуации.

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Этот код выполняется в дочернем процессе
        printf("Child process (PID: %d) is running\n", getpid());
    } else {
        // Этот код выполняется в родительском процессе
        printf("Parent process (PID: %d) is running\n", getpid());
    }

    return 0;
}
