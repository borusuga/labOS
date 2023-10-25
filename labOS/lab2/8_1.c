//
//  8_1.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// Посмотреть, что изменится, если читаемую процессами информацию сразу выводить на экран.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];

    int fd = open(inputFileName, O_RDONLY);
    if (fd == -1) {
        perror("Error opening input file");
        return 1;
    }

    // Create a child process
    pid_t childPid = fork();

    if (childPid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (childPid == 0) {  // Child process

        char buffer[4096];
        ssize_t bytesRead;
        

        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
                perror("Error writing to child output");
                exit(1);
            }
        }
        
        exit(0);
    } else {  // Parent process

        char buffer[4096];
        ssize_t bytesRead;

        printf("Contents of parent_output.txt:\n");
        
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
                perror("Error writing to parent output");
                return 1;
            }
        }

        // Wait for the child process to finish
        wait(NULL);
        
        close(fd);

        return 0;
    }
}
