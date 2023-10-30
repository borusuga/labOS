//
//  2.c
//  labOS
//
//  Created by Alyona Borushnova on 30.10.2023.
//

// Модифицировать программу п.1 так, чтобы вместо signal использовать sigaction.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct sigaction new_action, old_action;

void signal_handler(int signum) {
    
    printf("Received signal: %d\n", signum);
    
    // Восстанавливаем действие по умолчанию
    sigaction(signum, &old_action, NULL);
}

int main(int argc, char *argv[]) {
    
    printf("PID: %d\n", getpid());
    
    new_action.sa_handler = signal_handler;
    new_action.sa_flags = 0;
    sigemptyset(&new_action.sa_mask);

    // Установка нового действия с использованием sigaction
    if (sigaction(SIGUSR1, &new_action, &old_action) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Sending SIGUSR1...\n");
    // Отправляем  SIGUSR1
    kill(getpid(), SIGUSR1);

    while (1) {
        // Отправляем  SIGUSR1, чтобы увидеть реакцию на сигнал по умолчанию (завершился...)
        // kill -USR1 <PID>
    }

    return 0;
}
