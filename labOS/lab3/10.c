//
//  10_1.c
//  labOS
//
//  Created by Alyona Borushnova on 02.11.2023.
//

// Написать программу, иллюстрирующую способ блокирования дополнительных сигналов на время работы обработчика сигнала. Что произойдет, если во время обработки некоторого сигнала в процесс поступит несколько однотипных заблокированных сигналов.

// -> дождемся завершения сигнала, который блокирует доп сигналы
// -> будут в "очереди"
//    когда процесс снимает блокировку сигнала, все сигналы, которые были помещены в очередь сигналов, будут доставлены         процессу.
// но так как сигналы однотипные - схлопнутся в один

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


void custom_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Child received SIGUSR1, blocking SIGUSR2\n");
        
        // Блокируем SIGUSR2
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR2);
        sigprocmask(SIG_BLOCK, &mask, NULL);

        // Выполняем обработку SIGUSR1, игнорируя SIGINT
        printf("Handling SIGUSR1 in the child process...\n");
        sleep(5);

        printf("Finished handling SIGUSR1\n");

        // Разблокируем SIGUSR2
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
    }
}

// Обработчик сигнала SIGUSR2
void sigusr2_handler(int sign) {
    printf("Received signal: %d\n", sign);
}

int main(int argc, char *argv[]) {
    int child_status;
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Дочерний процесс
        printf("Child process (PID: %d) is running...\n", getpid());
        
        struct sigaction sa;
        sa.sa_handler = custom_handler;
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);
        
        // Устанавливаем обработчик сигнала SIGUSR2
        signal(SIGUSR2, sigusr2_handler);

        while (1) {
            // Бесконечный цикл, чтобы дочерний процесс продолжал работать
        }
    } else {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());

        sleep(1);  // Подождать, чтобы дать дочернему процессу время на настройку

        printf("Sending SIGUSR1 to the child process\n");
        kill(child_pid, SIGUSR1);

        sleep(1);
        
        printf("Sending SIGUSR2 to the child process...\n");
        kill(child_pid, SIGUSR2);
        kill(child_pid, SIGUSR2);
        kill(child_pid, SIGUSR2);
        
        sleep(5);
        
        kill(child_pid, SIGINT);

        sleep(1);  // Подождать, чтобы дочерний процесс обработал сигналы
        

        child_pid = waitpid(child_pid, &child_status, 0);

        if (WIFEXITED(child_status)) {
            printf("Child process terminated normally with status %d.\n", WEXITSTATUS(child_status));
        } else {
            printf("Child process terminated abnormally with status %d.\n", child_status);
        }
        
        printf("Parent process is terminating\n");
    }

    return 0;
}
