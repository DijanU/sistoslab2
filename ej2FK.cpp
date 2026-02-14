#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 1000000

void trabajo(char *nombre){
    for(long i = 0; i < N; i++){
        printf("%s: %ld\n", nombre, i);
    }
}

int main(){

    pid_t p1, p2, p3;
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    p1 = fork();

    if(p1 == 0){
        // HIJO
        p2 = fork();

        if(p2 == 0){
            // NIETO
            p3 = fork();

            if(p3 == 0){
                // BISNIETO
                trabajo("Bisnieto");
            }
            else{
                trabajo("Nieto");
                wait(NULL);
            }
        }
        else{
            trabajo("Hijo");
            wait(NULL);
        }
    }
    else{
        // PADRE
        trabajo("Padre");
        wait(NULL);

        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("\nTiempo total concurrente: %f segundos\n", tiempo);
    }

    return 0;
}