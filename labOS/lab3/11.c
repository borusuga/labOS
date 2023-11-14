//
//  11_term.c
//  labOS
//
//  Created by Alyona Borushnova on 08.11.2023.
//

// Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов. Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void handler(int sig) {
    printf("Received signal: %d\n", sig);
}

int main(void) {
    // Инициализируем обработчик сигнала SIGUSR1
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    
    // Создаем дочерний процесс
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        printf("Child process (PID: %d) is running...\n", getpid());

        sleep(5);
        // Отправляем сигнал SIGUSR1 родительскому процессу
        
        kill(getppid(), SIGUSR1);
        exit(0);
    } else {
        // Родительский процесс
        printf("Parent process (PID: %d) is running...\n", getpid());

        // Блокируем сигнал SIGUSR1 от всех процессов, кроме дочернего
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL);
        
        // Ждем сигнала SIGUSR1
        sigsuspend(&mask);
        
        // Сигнал получен, можно разблокировать сигнал SIGUSR1
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
        
        // Выводим сообщение
        printf("Parent: Signal SIGUSR1 recieved. Sync completed.\n");
    }
    
    return 0;
}
