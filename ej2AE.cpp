#include <stdio.h>
#include <time.h>

#define N 1000000

int main() {

    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    // Primer ciclo
    for(long i = 0; i < N; i++){
        printf("Ciclo 1: %ld\n", i);
    }

    // Segundo ciclo
    for(long i = 0; i < N; i++){
        printf("Ciclo 2: %ld\n", i);
    }

    // Tercer ciclo
    for(long i = 0; i < N; i++){
        printf("Ciclo 3: %ld\n", i);
    }

    fin = clock();

    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("\nTiempo total: %f segundos\n", tiempo);

    return 0;
}