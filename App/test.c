#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handler(int signum){

    printf("Yo ignore Ctrl+C");
}

int main(int arc,char** argv){

    signal(SIGINT,handler);
    while (1)
    {
        printf("Hola\n");
    }
    
}