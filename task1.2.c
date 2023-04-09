#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void exit_callback() { printf("Exited\n"); }

void main(int argc, char* argv[]) {
	atexit(exit_callback);

	int pid;
	switch (pid = fork()) {
		case -1:
			printf("Fork failed\n");
			exit(EXIT_FAILURE);
		default:
			printf("Arguments:\n");
			for (int i = 0; i < argc; i++) {
				printf("\t%s\n", argv[i]);
			}
			exit(EXIT_SUCCESS);
	}
}