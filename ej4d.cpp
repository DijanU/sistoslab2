#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid = fork();

    if(pid == 0){   // HIJO
        for(long i = 1; i <= 4000000; i++){
            printf("%ld\n", i);
        }
    }
    else{
        while(1);
    }

    return 0;
}