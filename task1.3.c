#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char*argv[]){

int pid;
switch(pid=fork()){
    case -1:
    printf("Fork failed\n");
    exit(EXIT_FAILURE);
    case 0:
    for(int i=1;i<argc;i+=2){
        int a=atoi(argv[i]);
        printf("%d\n",a*a);
    }
    exit(EXIT_SUCCESS);
    default:
    for(int i=2;i<argc;i+=2){
        int a=atoi(argv[i]);
        printf("%d\n",a*a);
    }
    exit(EXIT_SUCCESS);
}
}