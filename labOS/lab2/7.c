//
//  7.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Модифицировать программу, включив в нее setpgrp в порожденный процесс до того, как он будет выполнять pause.

// Повлияет ли на порожденный процесс нажатие клавиши прерывания в тот момент, когда родительский процесс "спит"?

// Будет ли показан порожденный процесс в выводе команды ps?

void child_process(void) {
    printf("Child process (PID: %d, Parent PID: %d, Group ID: %d)\n", getpid(), getppid(), getpgrp());
    setpgrp();
    printf("Child process after setpgrp (PID: %d, Parent PID: %d, Group ID: %d)\n", getpid(), getppid(), getpgrp());
    pause(); // Child process pauses, waiting for a signal
    printf("Child process (PID: %d, PPID: %d) is running.\n", getpid(), getppid());
    printf("Child process resumes after receiving a signal.\n");
    exit(EXIT_SUCCESS);
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
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]) {
    parent_process();
    return 0;
}

