#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
printf("%d\n", getpid());
printf("%d\n", getppid());
printf("%d\n", getuid());
printf("%d\n", geteuid());
printf("%d\n", getgid());
}