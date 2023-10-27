//
//  1_for10.c
//  labOS
//
//  Created by Alyona Borushnova on 27.10.2023.
//

#include <stdio.h>
#include <stdlib.h>

// Написать программу, которая добавляет новые строки в среду процесса.

extern char **environ;

void add_string(const char *key, const char *value) {
    if (setenv(key, value, 1) == 0) {
        printf("Added to the environment.\n");
    } else {
        perror("Error adding to the environment");
    }
}


int main(int argc, char *argv[]) {
    const char *string1 = argv[1];
    const char *string2 = argv[2];

    add_string(string1, string2);
    
    for (char **it = environ; *it; it++) {
        printf("%s\n", *it);
    }

}

