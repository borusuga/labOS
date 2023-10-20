//
//  10.c
//  labOS
//
//  Created by Alyona Borushnova on 20.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//Написать программу, которая выводит на экран содержимое файла в обратном порядке:
//сначала выводится последний символ файла, затем предпоследний и так далее до первого. Использовать lseek и read.

#define BUF_SIZE 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error (open)");
        exit(EXIT_FAILURE);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error (lseek)");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];
    ssize_t bytes_read;
    off_t current_position = file_size - 1;  // Start from the end of the file

    while (current_position >= 0) {
        if (lseek(fd, current_position, SEEK_SET) == -1) {
            perror("Error (lseek)");
            close(fd);
            exit(EXIT_FAILURE);
        }

        bytes_read = read(fd, buffer, 1);
        if (bytes_read == -1) {
            perror("Error (read)");
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (bytes_read == 0) {
            // Reached the end of the file
            break;
        }

        // Print the character (or byte) read
        write(STDOUT_FILENO, buffer, 1);

        current_position--;  // Move to the previous character
    }

    close(fd);
    return 0;
}
