#include <stdio.h>
#include <time.h>

int main() {

    clock_t inicio, fin;
    double tiempo;

    inicio = clock();   // antes del primer for

    for(long i = 0; i < 1000000; i++);
    for(long i = 0; i < 1000000; i++);
    for(long i = 0; i < 1000000; i++);

    fin = clock();      // después del último for

    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion: %f segundos\n", tiempo);

    return 0;
}