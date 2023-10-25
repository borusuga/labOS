//
//  3b.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// более структурированная

// Написать программу, в которой процесс порождает новый и позволяет порожденному процессу завершиться. Оба процесса должны выводить свои идентификаторы (процесса, родительского процесса, группы процессов). Проверить идентификатор и статус завершения порожденного процесса. Выполнить данную программу и посмотреть ее результаты.

void child(void) {
    // Код, выполняемый дочерним процессом
    printf("Child process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());
    exit(52);  // Дочерний процесс завершается с кодом 52
}

void parent(void) {
    printf("Parent process (PID: %d, Parent PID: %d, Group ID: %d)\n",
           getpid(), getppid(), getpgrp());

  pid_t pid = fork();
  if (pid == 0) {
    child();
  } else {
    printf("Waiting for child process to terminate...\n");
    int status;
    waitpid(pid, &status, 0);
    printf("Child process terminated with status: %d\n", WEXITSTATUS(status));
    printf("Ending parent process...\n");
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  parent();
  return 0;
}
