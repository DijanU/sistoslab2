#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_NAME "/ipc_shared_mem"
#define FIFO_NAME "/tmp/ipc_fifo"
#define SIZE 4096

int main(int argc, char *argv[]) {

    if(argc != 3){
        printf("Uso: ./ipc n x\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    /* ---------- MEMORIA COMPARTIDA ---------- */

    int created = 0;
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);

    if(shm_fd == -1){
        if(errno == EEXIST){
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
            printf("Memoria ya existia\n");
        } else {
            perror("shm_open");
            exit(1);
        }
    } else {
        created = 1;
        ftruncate(shm_fd, SIZE);
        printf("Memoria creada por este proceso\n");
    }

    /* ---------- FIFO PARA ENVIAR FD ---------- */

    mkfifo(FIFO_NAME, 0666);

    if(created){
        int fifo = open(FIFO_NAME, O_WRONLY);
        write(fifo, &shm_fd, sizeof(int));
        printf("Envié mi FD: %d\n", shm_fd);
        close(fifo);
    } else {
        int fifo = open(FIFO_NAME, O_RDONLY);
        int received_fd;
        read(fifo, &received_fd, sizeof(int));
        printf("Recibí FD: %d\n", received_fd);
        close(fifo);
    }

    /* ---------- MAPEO ---------- */

    char *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }

    /* ---------- PIPE PADRE-HIJO ---------- */

    int p[2];
    pipe(p);

    pid_t pid = fork();

    if(pid > 0){ // PADRE
        close(p[0]);

        for(int i=0;i<SIZE;i++){
            if(i % n == 0){
                write(p[1], &x, 1);
            }
        }

        close(p[1]);
        wait(NULL);

        printf("Contenido memoria:\n%s\n", ptr);
    }
    else{ // HIJO
        close(p[1]);

        char c;
        int index=0;

        while(read(p[0], &c, 1) > 0){
            ptr[index++] = c;
        }

        ptr[index]='\0';
        close(p[0]);
        exit(0);
    }

    /* ---------- LIMPIEZA ---------- */

    munmap(ptr, SIZE);
    close(shm_fd);

    if(created)
        shm_unlink(SHM_NAME);

    return 0;
}