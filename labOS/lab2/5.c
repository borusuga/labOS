//
//  5.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

/*
 ./l2_5 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// более простая

// Изменить программу п. 3 так, чтобы родительский процесс выполнялся, не ожидая завершения порожденного процесса. Что произойдет с порожденным процессом, когда он завершится? Как убить зомби?


//int main(int argc, char *argv[]) {
//    pid_t child_pid;
//
//    printf("Parent process (PID: %d) is running\n", getpid());
//
//    child_pid = fork();
//
//    if (child_pid == 0) {
//        // Этот код будет выполнен в дочернем процессе
//        printf("Child process (PID: %d) is running\n", getpid());
//        sleep(10);
//        printf("Child process is terminated\n");
//    } else if (child_pid > 0) {
//        // Этот код будет выполнен в родительском процессе
//        printf("Parent process is continuing without waiting for the child\n");
//    } else {
//        perror("Fork failed");
//        return 1;
//    }
//
//    return 0;
//}

int main(int argc, char *argv[]) {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {  // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        // Дочерний процесс завершается
        exit(EXIT_SUCCESS);
    } else {  // Parent process
        printf("Parent process (PID: %d) is running.\n", getpid());
        // Не вызываем wait, чтобы не собирать статус завершения дочернего процесса
        // -> дочерний процесс станет зомби

        // Ждем , чтобы можно было все увидеть
        sleep(10);
    }

    return 0;
}

//Когда дочерний процесс завершится, он пройдет в состояние "зомби" (zombie). В состоянии зомби процесс все еще остается в списке процессов, но не выполняет какую-либо активную работу. Он ожидает, что родительский процесс считает его статус завершения с помощью системного вызова wait() или waitpid(). Когда родительский процесс успешно считает статус завершения зомби-процесса, ресурсы, связанные с этим процессом, будут освобождены, и процесс будет полностью удален из системы.
//В этой программе, поскольку родительский процесс не выполняет ожидание дочернего процесса (нет системного вызова wait() или waitpid()), дочерний процесс станет зомби, но он не будет удален из системы до завершения родительского процесса. Когда родительский процесс завершится, система автоматически освободит ресурсы, связанные с зомби-процессом.
