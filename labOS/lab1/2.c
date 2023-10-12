//
//  2.c
//  labOS
//
//  Created by Alyona Borushnova on 11.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main2(int argc, char *const argv[]) {
    int opt;
    const char *filename = NULL;
    int access_rights = 0;
    
    while ((opt = getopt(argc, argv, "rw")) != -1) {
        printf("opt '%c'\n", opt);
        switch (opt) {
            case 'r':
                access_rights |= S_IRUSR;
                break;
            case 'w':
                access_rights |= S_IWUSR;
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
    printf("optind '%d'\n", optind);

    if (optind < argc) {
        filename = argv[optind];
    }
    
    printf("filename '%s'\n", filename);
    printf("access_rights '%d'\n", access_rights);

    if (filename == NULL || access_rights == 0) {
        fprintf(stderr, "Usage: %s <filename> (-[rw])+\n", argv[0]);
        return 1;
    }
    
    // Step 1: Create a new file with specified access rights
    int file_descriptor = open(filename, O_CREAT | O_WRONLY, access_rights);

    if (file_descriptor == -1) {
        perror("Error (open)");
        return 1;
    }
    printf("File '%s' created successfully with access rights %s%s.\n", filename, (access_rights & S_IRUSR) ? "read" : "", (access_rights & S_IWUSR) ? "write" : "");
    
    // Step 2: Write some data to the file
    const char *data = "This is some data written to the file.";
    write(file_descriptor, data, strlen(data));
    close(file_descriptor);
    
    // Step 3: Attempt to open the file for reading
    file_descriptor = open(filename, O_RDONLY);

    if (file_descriptor == -1) {
        perror("Error (open for reading)");
    } else {
        printf("File '%s' opened successfully for reading.\n", filename);

        // Read and display the contents of the file
        char buffer[256];
        ssize_t bytes_read;

        printf("Contents of the file:\n");
        while ((bytes_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(file_descriptor);
    }

    // Step 4: Attempt to open the file for reading and writing
    file_descriptor = open(filename, O_RDWR);

    if (file_descriptor == -1) {
        perror("Error (open for reading and writing)");
    } else {
        printf("File '%s' opened successfully for reading and writing.\n", filename);
        close(file_descriptor);
    }
    
    return 0;
}
