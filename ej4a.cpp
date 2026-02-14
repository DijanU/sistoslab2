#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid = fork();

    if(pid == 0){   // HIJO
        printf("Hola, soy el proceso hijo (PID %d)\n", getpid());
    }
    else{           // PADRE
        while(1);   // ciclo infinito
    }

    return 0;
}