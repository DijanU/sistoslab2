#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SIZE 4096
#define SHM_NAME "/mi_memoria"

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Uso: ./ipc a|b\n");
        exit(1);
    }

    char letra = argv[1][0];

    if(letra != 'a' && letra != 'b'){
        printf("Debe usar a o b\n");
        exit(1);
    }

    int fd;
    char *ptr;

    /* abrir o crear memoria compartida */
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if(fd == -1){
        perror("shm_open");
        exit(1);
    }

    /* definir tamaño */
    if(ftruncate(fd, SIZE) == -1){
        perror("ftruncate");
        exit(1);
    }

    /* mapear memoria */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }

    /* escribir en la memoria */
    for(int i = 0; i < 200; i++){
        ptr[i] = letra;
        usleep(20000);   // para que se intercalen a y b
    }

    /* imprimir contenido */
    printf("Contenido memoria:\n");
    for(int i = 0; i < 200; i++){
        printf("%c", ptr[i]);
    }
    printf("\n");

    munmap(ptr, SIZE);
    close(fd);

    return 0;
}