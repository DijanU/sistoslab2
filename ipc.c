#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define SHM_NAME "/mi_memoria"
#define SIZE 4096

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Uso: ./ipc a|b\n");
        return 1;
    }

    char letra = argv[1][0];

    // abrir o crear memoria compartida
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if(fd == -1){
        perror("shm_open");
        return 1;
    }

    // asignar tamaño
    ftruncate(fd, SIZE);

    // mapear memoria
    void *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        return 1;
    }

    // ----- AQUI ESTA EL CAMBIO IMPORTANTE -----

    // primer espacio: entero compartido (indice global)
    int *pos = (int*) ptr;

    // despues del entero comienza el buffer real
    char *data = (char*)ptr + sizeof(int);

    // si es la primera vez, inicializamos posicion
    if(*pos == 0){
        *pos = 0;
    }

    srand(getpid());

    // escribir 50 caracteres
    for(int i = 0; i < 50; i++){

        int index = *pos;          // leer posicion compartida
        data[index] = letra;       // escribir
        (*pos)++;                  // avanzar posicion global

        usleep((rand() % 200) * 1000); // dormir random
    }

    sleep(1);

    // solo uno imprime (el que llega de ultimo normalmente)
    printf("\nContenido memoria:\n");
    write(STDOUT_FILENO, data, *pos);
    printf("\n");

    munmap(ptr, SIZE);
    close(fd);

    return 0;
}