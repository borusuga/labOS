//
//  4.c
//  labOS
//
//  Created by Alyona Borushnova on 18.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main4(int argc, char *const argv[]) {
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
    
    // Step 1: Create a new file with specified access rights (wr)
    int file_descriptor = open(filename, O_CREAT | O_RDWR | O_TRUNC, access_rights);
    
    if (file_descriptor == -1) {
        perror("Error (open)");
        return 1;
    }
    printf("File '%s' created successfully with access rights %s%s.\n", filename, (access_rights & S_IRUSR) ? "read" : "", (access_rights & S_IWUSR) ? "write" : "");
    
    
    // Read and write operations with different positioning methods
    const char *data = "This is some data written to the file.\n";
    // Write default bhv
    write(file_descriptor, data, strlen(data));
    
    char buffer[256];
    ssize_t bytes_read;
    
    // Seek to the beginning
    lseek(file_descriptor, 0, SEEK_SET);
    
    // Read default bhv
    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    printf("Read at the current position (0):\n%s\n", buffer);
    
    memset(buffer, 0, sizeof(buffer));
    
    // Seek to a specific position (10 bytes from the beginning)
    lseek(file_descriptor, 10, SEEK_SET);

    // Read from the current position
    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    printf("Read at the current position (10):\n%s\n", buffer);

    // Seek to a different position (20 bytes from the beginning)
    lseek(file_descriptor, 20, SEEK_SET);
    
    // Write data at the new position
    printf("Write data at the new position (20)\n");
    const char *new_data = "New data written at a different position.\n";
    write(file_descriptor, new_data, strlen(new_data));
    
    // Read from the current position
    memset(buffer, 0, sizeof(buffer));
    lseek(file_descriptor, 0, SEEK_SET);
    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    printf("Read at the current position (0):\n%s\n", buffer);
    
    
//    //Reverse lseek
//    // Get the size of the file
//    off_t file_size = lseek(file_descriptor, 0, SEEK_END);
//
//    if (file_size == -1) {
//        perror("Error (lseek)");
//        close(file_descriptor);
//        return 1;
//    }
//    // Read the file in reverse order character by character
//    char ch;
//    printf("File data in reverse order:\n");
//    for (off_t position = file_size - 1; position >= 0; position--) {
//        if (lseek(file_descriptor, position, SEEK_SET) == -1) {
//            perror("Error (lseek)");
//            break;
//        }
//        if (read(file_descriptor, &ch, 1) == -1) {
//            perror("Error (read)");
//            break;
//        }
//        putchar(ch);
//    }
    
    // Seek beyond the end of the file and attempt to read (beyond EOF)
    printf("Seek beyond the end of the file and attempt to read (beyond EOF)\n\n");
    memset(buffer, 0, sizeof(buffer));
    lseek(file_descriptor, 100, SEEK_SET);
    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    if (bytes_read == 0) {
        printf("Read beyond the end of the file (EOF).\n");
    }
    
    // Seek beyond the end of the file and attempt to write (extend the file)
    printf("Seek beyond the end of the file and attempt to write (extend the file)\n");
    lseek(file_descriptor, 100, SEEK_SET);
    const char *new_data2 = "New data written beyond the end of the file.\n";
    write(file_descriptor, new_data2, strlen(new_data2));
    printf("Data written beyond the end of the file.\n\n");
    
    memset(buffer, 0, sizeof(buffer));
    // Seek to the beginning of the file
    lseek(file_descriptor, 0, SEEK_SET);

    // Read the entire file
    ssize_t total_bytes_read = 0;
    printf("Read at the current position (0):\n");
    while ((bytes_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
          fwrite(buffer, 1, bytes_read, stdout);
          total_bytes_read += bytes_read;
    }

    // Print the total bytes read
    printf("Total bytes read: %zd\n", total_bytes_read);
    
    
    close(file_descriptor);
    
    return 0;
}
