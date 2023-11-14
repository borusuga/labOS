//
//  8.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Включить в порожденный процесс системный вызов signal, переопределяющий стандартную реакцию на сигнал (для внешнего цикла установить в функции максимальное значение параметра цикла). Что изменится?

// верхняя граница успеет меняться

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int max_iter = 6000;
int INT_MAX = 8000;

// Обработчик сигнала SIGUSR1
void child_handler(int sign) {
    max_iter = INT_MAX; // Устанавливаем максимальное значение параметра цикла
    printf("Received signal: %d\n", sign);
    printf("Received signal: %d\n", sign);
    printf("Received signal: %d\n", sign);
    printf("Received signal: %d\n", sign);
    printf("Received signal: %d\n", sign);
    printf("Received signal: %d\n", sign);
}

int main(int argc, char *argv[]) {
    int child_status;
    // Создаем дочерний процесс
    pid_t pid = fork();

    if (!pid) {
        // Дочерний процесс
        printf("Child process (PID: %d) is running...\n", getpid());
        // Устанавливаем обработчик сигнала SIGUSR1
        signal(SIGUSR1, child_handler);
        
        for (int i = 1; i <= max_iter; ++i) {
            printf("Дочерний процесс: Итерация i: %d\n", i);
            for (int j = 0; j < 100000; ++j);
            
        }
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());
        // Ожидаем некоторое время, чтобы дать дочернему процессу запуститься
        sleep(1);
        // Посылаем сигнал SIGUSR1 в дочерний процесс
        kill(pid, SIGUSR1);
        // Ожидаем завершения дочернего процесса
        pid = waitpid(pid, &child_status, 0);

        if (WIFEXITED(child_status)) {
            printf("Child process terminated normally with status %d.\n", WEXITSTATUS(child_status));
        } else {
            printf("Child process terminated abnormally.\n");
        }
    } else if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}

