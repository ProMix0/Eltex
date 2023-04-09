#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void getLine(char* str) {
	char c;
	while ((c = getchar()) != '\n') {
		*str = c;
		str++;
	}
	*str = 0;
}

void parseArgs(char* str, char** args) {
	char waitStart = 1;
	int j = 0;
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == ' ') {
			waitStart = 1;
			str[i] = 0;
			continue;
		}
		if (waitStart) {
			waitStart = 0;
			args[j] = str + i;
			j++;
		}
	}
	args[j] = 0;
}

void main(int argc, char* argv[]) {
	int status;
	while (1) {
		printf("> ");

		char str[128];
		getLine(str);
		char* args[16];

		parseArgs(str, args);

		int pid = fork();

		switch (pid) {
			case 0:
				status = execvp(args[0], args);
				printf("Run failed with status code %d\n", status);
				exit(EXIT_FAILURE);
			case -1:
				printf("Fail while forking\n");
				exit(EXIT_FAILURE);
			default:
				wait(&status);
				if (status)
					printf("Child process exited with non-zero code %d\n",
						   status);
				break;
		}
	}
}