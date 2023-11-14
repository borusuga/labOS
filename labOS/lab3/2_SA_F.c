//
//  1_SA_F.c
//  labOS
//
//  Created by Alyona Borushnova on 10.11.2023.
//

//  Изменить реакцию процесса на некоторый сигнал при помощи signal. В функции обработчике переустановить реакцию на сигнал на значение по умолчанию. Запустить программу и объяснить наблюдаемый результат.

// вместо переустановки реакции в обработчике - установили флаг SA_RESETHAND

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/** Пользовательская функция-обработчик SIGUSR1 */
void signal_handler(int signum) {
    
    printf("Received signal: %d\n", signum);
    
    // Восстанавливаем действие по умолчанию
    signal(signum, SIG_DFL);
}

int main(int argc, char *argv[]) {
    
    printf("PID: %d\n", getpid());
    
    signal(SIGUSR1, signal_handler);

    printf("Sending SIGUSR1...\n");
    // Отправляем  SIGUSR1
    kill(getpid(), SIGUSR1);

    while (1) {
        // Отправляем  SIGUSR1, чтобы увидеть реакцию на сигнал по умолчанию (завершился...)
        // kill -USR1 <PID>                                                  (SIGUSR1)
    }
    
    return 0;
}
