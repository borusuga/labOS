//
//  3.c
//  labOS
//
//  Created by Alyona Borushnova on 13.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//Повторно выполнить программу п. 2 с теми же исходными данными;
//проверить результаты выполнения каждого системного вызова. Объяснить полученные результаты.


int main(int argc, char *const argv[]) {
    int opt;
    const char *filename = NULL;
    int access_rights = 0;
    
    while ((opt = getopt(argc, argv, "rw")) != -1) {
        switch (opt) {
            case 'r':
                access_rights |= S_IRUSR | S_IRGRP | S_IROTH;
                break;
            case 'w':
                access_rights |= S_IWUSR | S_IWGRP | S_IWOTH;
                break;
            case '?':
                if (optopt == 'r' || optopt == 'w') {
                    fprintf(stderr, "Option -%c requires a filename argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option -%c\n", optopt);
                }
                break;
            default:
                abort();
        }
    }

    if (optind < argc) {
        filename = argv[optind];
    }

    if (filename == NULL || access_rights == 0) {
        fprintf(stderr, "Usage: %s (-[rw])+ <filename>\n", argv[0]);
        return 1;
    }
        
    // Step 1: Create a new file with specified access rights
    int file_descriptor = open(filename, O_CREAT | O_WRONLY | O_TRUNC, access_rights);
    printf("open: %s\n", strerror(errno));
    if (file_descriptor == -1) {
        perror("Error (open)");
        return 1;
    }
    
    printf("File '%s' created successfully with access rights %s%s.\n", filename, (access_rights & S_IRUSR) ? "read" : "", (access_rights & S_IWUSR) ? "write" : "");
    
    // Step 2: Write some data to the file
    const char *data = "This is some data written to the file.";
    write(file_descriptor, data, strlen(data));
    printf("write: %s\n", strerror(errno));
    close(file_descriptor);
    printf("close: %s\n", strerror(errno));
    
    // Step 3: Attempt to open the file for reading
    file_descriptor = open(filename, O_RDONLY);
    printf("open: %s\n", strerror(errno));

    if (file_descriptor == -1) {
        perror("Error (open for reading)");
    } else {
        printf("File '%s' opened successfully for reading.\n", filename);

        // Read and display the contents of the file
        char buffer[256];
        ssize_t bytes_read;

        bytes_read = read(file_descriptor, buffer, sizeof(buffer));
        printf("read: %s\n", strerror(errno));
        if (bytes_read < 0) {
            perror("Error (read)");
        } else {
            printf("Message:\n%s\n(read %zd bytes)\n", buffer, bytes_read);
        }
        close(file_descriptor);
    }

    // Step 4: Attempt to open the file for reading and writing
    file_descriptor = open(filename, O_RDWR);
    printf("open: %s\n", strerror(errno));
    if (file_descriptor == -1) {
        perror("Error (open for reading and writing)");
    } else {
        printf("File '%s' opened successfully for reading and writing.\n", filename);
        close(file_descriptor);
        printf("close: %s\n", strerror(errno));
    }
    
    return 0;
}
