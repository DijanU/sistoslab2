#include <unistd.h>
#include <sys/wait.h>

int main(){

    if(fork()==0){
        execl("./ipc","ipc","5","a",NULL);
    }

    usleep(200000); // 0.2s para sincronizar

    if(fork()==0){
        execl("./ipc","ipc","7","b",NULL);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}