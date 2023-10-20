//
//  9.c
//  labOS
//
//  Created by Alyona Borushnova on 19.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//Изменить программу п. 8 таким образом, чтобы функция копирования
//использовала стандартные ввод и вывод, а вызывающая программа переназначала стандартные ввод и вывод на указанные в аргументах командной строки файлы.

#define BUF_SIZE 256

// Function to copy data from standard input to standard output
int copyFile(void) {
    ssize_t bytes_read;
    char buffer[BUF_SIZE];

    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("Error (write)");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int source_fd, dest_fd;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s [source_file destination_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Error (open source)");
        exit(EXIT_FAILURE);
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (dest_fd == -1) {
        perror("Error (open destination)");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    if (dup2(source_fd, STDIN_FILENO) == -1) {
        perror("Error (dup2 source)");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    if (dup2(dest_fd, STDOUT_FILENO) == -1) {
        perror("Error (dup2 destination)");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    if (copyFile() == -1) {
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    close(source_fd);
    close(dest_fd);

    return 0;
}
