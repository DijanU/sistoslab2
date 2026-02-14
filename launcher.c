#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(1);
    }

    /* HIJO */
    if(pid == 0){
        execl("./ipc", "ipc", "a", NULL);
        perror("execl hijo");
        exit(1);
    }
    /* PADRE */
    else{
        execl("./ipc", "ipc", "b", NULL);
        perror("execl padre");
        exit(1);
    }

    return 0;
}