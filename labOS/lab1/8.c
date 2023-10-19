//
//  8.c
//  labOS
//
//  Created by Alyona Borushnova on 19.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256  // Buffer size

int main8(int argc, char *argv[]) {
    
    int source_fd, dest_fd;
    ssize_t bytes_read;
    char buffer[BUF_SIZE];

    // Determine the input and output file descriptors
    if (argc == 1) {
        source_fd = STDIN_FILENO;  // Use standard input
        dest_fd = STDOUT_FILENO;  // Use standard output
    } else if (argc == 3) {
        // Open the source file for reading
        source_fd = open(argv[1], O_RDONLY);
        if (source_fd == -1) {
            perror("Error (open source)");
            exit(EXIT_FAILURE);
        }

        // Create or open the destination file for writing
        dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
        if (dest_fd == -1) {
            perror("Error (open destination)");
            close(source_fd);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Usage: %s [source_file destination_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Perform the file copy
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error (write)");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Close the file descriptors
    close(source_fd);
    close(dest_fd);

    return 0;
}


