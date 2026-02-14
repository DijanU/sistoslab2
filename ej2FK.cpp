#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t hijo, nieto, bisnieto;
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();   // antes del primer fork

    hijo = fork();

    if(hijo == 0){   // PROCESO HIJO

        nieto = fork();

        if(nieto == 0){   // PROCESO NIETO

            bisnieto = fork();

            if(bisnieto == 0){   // PROCESO BISNIETO
                for(long i = 0; i < 1000000; i++);
            }
            else{
                for(long i = 0; i < 1000000; i++);
                wait(NULL);
            }
        }
        else{
            for(long i = 0; i < 1000000; i++);
            wait(NULL);
        }
    }
    else{   // PROCESO PADRE (RAÍZ)
        wait(NULL);
        fin = clock();

        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo concurrente: %f segundos\n", tiempo);
    }

    return 0;
}