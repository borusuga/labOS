//
//  8_1.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

/*
 ./l2_8_1 input.txt 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// Посмотреть, что изменится, если читаемую процессами информацию сразу выводить на экран.
// -> все норм выведется 

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

        char buffer[1];
        ssize_t bytesRead;

        printf("Contents of child output:\n");

        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            char newbuf[2];
            newbuf[0] = buffer[0];
            newbuf[1] = '+';
            if (write(STDOUT_FILENO, newbuf , bytesRead + 1) == -1) {
                perror("Error writing to child output file");
                exit(1);
            }
        }

        exit(0);
    } else {  // Parent process

        char buffer[1];
        ssize_t bytesRead;

        printf("\nContents of parent output:\n");
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            char newbuf[2];
            newbuf[0] = buffer[0];
            newbuf[1] = '-';
            if (write(STDOUT_FILENO, newbuf, bytesRead+1) == -1) {
                perror("Error writing to parent output file");
                return 1;
            }
        }

        // Wait for the child process to finish
        wait(NULL);
        
        close(fd);

        return 0;
    }
}

