//
//  6.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Изменить программу п. 3 так, чтобы оба процесса выполняли системный вызов pause после вывода идентификаторов. Запустить программу в фоновом режиме и посмотрите (с помощью ps), какие процессы существуют для данного пользователя. Выполнить kill -9 pid для родительского процесса. Что произойдет с порожденным?
// -> стал сиротой

// После очистки текущего сеанса, вновь выполнить программу, но уже в интерактивном режиме. Нажать на терминале клавишу CTRL-C. Что произойдет с родительским и порожденным процессами?
// -> завершились

// Можно ли получить такой же результат, если нажать клавишу прерывания после того, как родительский процесс завершится?
// -> Нажав CTRL-C после того, как родительский процесс завершится, ничего не произойдет, так как порожденный процесс уже стал зомби и ожидает завершения.
void child_process(void) {
    printf("Child process (PID: %d, PPID: %d) is running.\n", getpid(), getppid());
    pause(); // Child process pauses, waiting for a signal
    printf("Child process (PID: %d, PPID: %d) is running.\n", getpid(), getppid());
    printf("Child process resumes after receiving a signal.\n");
}

void parent_process(void) {
    printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n", getpid(), getppid(), getpgrp());
    
    pid_t pid = fork();
    if (pid == 0) {
        child_process();
    } else {
        printf("Parent process (PID: %d) is running.\n", getpid());
        
        
        // Kill the parent process using "kill -9 <pid>"
        printf("Kill the parent process with 'kill -9 %d'\n", getpid());
        // Uncomment the next line and run it from the terminal (be careful!)
        //kill(getpid(), SIGKILL);
        
        pause(); // Parent process pauses, waiting for a signal
        printf("Parent process resumes after receiving a signal.\n");
    }
}

int main(int argc, char *argv[]) {
    parent_process();
    return 0;
}

