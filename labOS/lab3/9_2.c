//
//  9_2.c
//  labOS
//
//  Created by Alyona Borushnova on 08.11.2023.
//

// Включить в порожденный процесс вместо системного вызова kill системный вызов alarm с перехватом сигнала. Что изменится?

// -> Child process terminated normally with status 0

/* После выполнения системного вызова alarm порожденный процесс будет получать сигнал SIGALRM через заданный интервал времени.
 * Если порожденный процесс обработает сигнал SIGALRM, то он может выполнить какие-либо действия и продолжить выполнение.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int max_iter = 10000;
int INT_MAX = 20000;

// Обработчик сигнала SIGALRM
void alarm_handler(int sign) {
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
        // Устанавливаем обработчик сигнала SIGALRM
        signal(SIGALRM, alarm_handler);
        alarm(1);
        for (int i = 1; i <= max_iter; ++i) {
            printf("Дочерний процесс: Итерация i: %d\n", i);
            for (int j = 0; j < 100000; ++j);
            
        }
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());
        // Ожидаем некоторое время, чтобы дать дочернему процессу запуститься
        sleep(5);
        // Посылаем сигнал SIGUSR1 в дочерний процесс
        kill(pid, SIGUSR1); // (не обрабатывается, тк дочерний уже завершён)
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

