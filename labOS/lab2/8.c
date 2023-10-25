//
//  8.c
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

// Открыть файл (достаточно большого размера), доступный для чтения. Имя файла передается из командной строки.
// После открытия файла создать параллельный процесс с помощью только fork. В обоих процессах создать свои файлы для записи, читать информацию из общего файла и копировать ее в собственные выходные файлы (не на экран).
// Вывести на экран содержимое полученных файлов из порожденного процесса по окончании записи в файл и из родительского процесса, дождавшись завершения порожденного процесса.

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
        int childOutputFile = open("child_output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (childOutputFile == -1) {
            perror("Error opening child output file");
            exit(1);
        }

        char buffer[4096];
        ssize_t bytesRead;

        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            if (write(childOutputFile, buffer, bytesRead) == -1) {
                perror("Error writing to child output file");
                exit(1);
            }
        }

        close(childOutputFile);
        exit(0);
    } else {  // Parent process
        int parentOutputFile = open("parent_output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (parentOutputFile == -1) {
            perror("Error opening parent output file");
            return 1;
        }

        char buffer[4096];
        ssize_t bytesRead;

        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            if (write(parentOutputFile, buffer, bytesRead) == -1) {
                perror("Error writing to parent output file");
                return 1;
            }
        }

        close(parentOutputFile);

        // Wait for the child process to finish
        wait(NULL);
        
        close(fd);

        // Now we can display the contents of the output files
        printf("Contents of child_output.txt:\n");
        system("cat child_output.txt");

        printf("\nContents of parent_output.txt:\n");
        system("cat parent_output.txt");

        return 0;
    }
}
