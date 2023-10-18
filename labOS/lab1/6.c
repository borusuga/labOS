//
//  6.c
//  labOS
//
//  Created by Alyona Borushnova on 18.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

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

    // Create a new file with read and write permissions
    int file_descriptor = open(filename, O_CREAT | O_RDWR | O_TRUNC, access_rights);

    if (file_descriptor == -1) {
        perror("Error (open)");
        return 1;
    }
    printf("File '%s' created successfully with access rights %s%s.\n", filename, (access_rights & S_IRUSR) ? "read" : "", (access_rights & S_IWUSR) ? "write" : "");

    // Move the cursor to a position beyond the end of the file
    lseek(file_descriptor, 1024 * 1024, SEEK_SET);

    // Write data at that position to create a sparse region
    char data = 'A';
    write(file_descriptor, &data, 1);

    // Close the file
    close(file_descriptor);
    
    
    struct stat file_stats;
    if (stat(filename, &file_stats) == -1) {
        perror("Error (stat)");
        return 1;
    }
    
    off_t file_size = file_stats.st_size;
    off_t block_size = file_stats.st_blksize;
    off_t apparent_size = file_stats.st_blocks * block_size;
    
    printf("File size: %lld bytes\n", file_size);
    printf("Apparent size: %lld bytes\n", apparent_size);

    if (file_size < apparent_size) {
        printf("File '%s' is a sparse file.\n", filename);
    } else {
        printf("File '%s' is not a sparse file.\n", filename);
    }

    return 0;
}
