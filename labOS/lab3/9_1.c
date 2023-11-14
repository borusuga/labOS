//
//  9_1.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Включить в порожденный процесс вместо системного вызова kill системный вызов alarm без перехвата сигнала. Что изменится?

// -> Child process terminated abnormally.

/* После выполнения системного вызова alarm порожденный процесс будет получать сигнал SIGALRM через заданный интервал времени.
 * Если порожденный процесс не обработает сигнал SIGALRM, то он будет прерван и перейдет в состояние ожидания завершения.
 * Родительский процесс, который создал порожденный процесс, будет уведомлен о завершении порожденного процесса. */

/* Таким образом, основное отличие между использованием системного вызова kill и системного вызова alarm без перехвата сигнала заключается в том, что в первом случае порожденный процесс завершается немедленно, а во втором случае порожденный процесс завершается через заданный интервал времени. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int max_iter = 10000;

int main(int argc, char *argv[]) {
    int child_status;
    // Создаем дочерний процесс
    pid_t pid = fork();

    if (!pid) {
        // Дочерний процесс
        printf("Child process (PID: %d) is running...\n", getpid());
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
            printf("Child process terminated abnormally with status %d.\n", child_status);
        }
    } else if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}

