//
//  1.c
//  labOS
//
//  Created by Alyona Borushnova on 08.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//Написать программу, которая выполняет некоторый системный вызов, например open, и затем выводит возвращаемую ошибку.
//Использовать в программе разные способы вывода сообщения об ошибке:
//вывод значения errno, вывод соответствующего сообщения из системного массива сообщений об ошибках sys_errlist[], вызов библиотечной функции perror.

int main(int argc, const char * argv[]) {
    const char *filename = argv[1];
    int file_descriptor = open(filename, O_RDONLY);
    printf("Task 1\n");
    
    if (file_descriptor == -1) {
        // Method 1: Output errno value
        printf("Error (errno): %d\n", errno);

        // Method 2: Output corresponding message from sys_errlist[]
        printf("Error (sys_errlist): %s\n", sys_errlist[errno]);

        // Method 3: Use the perror function
        perror("Error (perror)");
    } else {
        printf("File opened successfully!\n");
        close(file_descriptor);
    }
        
    return 0;
}
