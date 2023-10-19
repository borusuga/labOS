//
//  11.c
//  labOS
//
//  Created by Alyona Borushnova on 20.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [file1] [file2] [file3] ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    off_t max_length = 0;
    char *max_length_file = NULL;

    for (int i = 1; i < argc; i++) {
        char *filename = argv[i];
        struct stat st;

        if (stat(filename, &st) == -1) {
            perror("Error (stat)");
            continue;
        }

        if (S_ISREG(st.st_mode) && st.st_size > max_length) {
            max_length = st.st_size;
            max_length_file = filename;
        }
    }

    if (max_length_file) {
        printf("The longest file is: %s\n", max_length_file);
        printf("Length in bytes: %lld\n", (long long)max_length);
    } else {
        printf("No regular files found in the command line arguments.\n");
    }

    return 0;
}
