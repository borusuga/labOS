//
//  1.c
//  labOS
//
//  Created by Alyona Borushnova on 22.10.2023.
//

/*
 ./l2_1 
 */

#include <stdio.h>
#include <stdlib.h>

// Написать программу, которая добавляет новые строки в среду процесса.

extern char **environ;

void add_string(void) {
    char *str = calloc(80, sizeof(char));
    printf("enter string: ");
    scanf("%s", str);
//    "NEW_VARIABLE=SomeNewValue"
    if (putenv(str) == 0) {
        printf("Added NEW_VARIABLE to the environment.\n");
    } else {
        perror("Error adding NEW_VARIABLE");
    }
}

void print_env(void) {
    char *var_name = calloc(80, sizeof(char));
    printf("enter var name: ");
    scanf("%s", var_name);

    const char *value = getenv(var_name);
    if (value) {
        printf("%s\n", value);
    }
    else {
        perror("No value found\n");
    }
    free(var_name);
}

int main(int argc, char *argv[]) {
    int r, s = 1;
    do {
        printf("0 - add string\n1 - get env var\n2 - get env\n");
        s = scanf("%d", &r);
        switch(r) {
            case 0:
                add_string();
                break;
            case 1:
                print_env();
                break;
            default:
                for (char **it = environ; *it; it++) {
                    printf("%s\n", *it);
                }
                break;
        }
    } while(s);
}
