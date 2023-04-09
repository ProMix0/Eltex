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

int parseArgs(char* str, char** args) {
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
	return j;
}

int handleCommands(char* args[], int argsLen, char** calls[]) {
	int count = 1;
	*calls = args;
	calls++;
	for (int i = 0; i < argsLen; i++) {
		if (args[i][0] == '|' && args[i][1] == 0) {
			*calls = args + i + 1;
			calls++;
			args[i] = 0;
			count++;
		}
	}
	return count;
}

void main(int argc, char* argv[]) {
	int status;
	while (1) {
		printf("> ");

		char str[128];
		getLine(str);
		char* args[16];

		int argsCount = parseArgs(str, args);

		char** calls[8];
		int callsCount = handleCommands(args, argsCount, calls);

		int pipesArr[callsCount * 2];
		for (int i = 0; i < callsCount - 1; i++) {
			pipe(pipesArr + 1 + i * 2);
			int swap = pipesArr[1 + i * 2];
			pipesArr[1 + i * 2] = pipesArr[2 + i * 2];
			pipesArr[2 + i * 2] = swap;
		}
		pipesArr[0] = STDIN_FILENO;
		pipesArr[callsCount * 2 - 1] = STDOUT_FILENO;

		for (int i = 0; i < callsCount; i++) {
			int pid = fork();

			switch (pid) {
				case 0:
					int res1 = dup2(pipesArr[i * 2], STDIN_FILENO);
					int res2 = dup2(pipesArr[i * 2 + 1], STDOUT_FILENO);

					for (int i = 1; i < callsCount * 2 - 1; i++)
						close(pipesArr[i]);

					status = execvp(*calls[i], *(calls + i));
					fprintf(stderr, "Run failed with status code %d\n", status);
					exit(EXIT_FAILURE);
				case -1:
					printf("Fail while forking\n");
					exit(EXIT_FAILURE);
			}
		}
		for (int i = 1; i < callsCount * 2 - 1; i++) close(pipesArr[i]);
		for (int i = 0; i < callsCount; i++) {
			wait(&status);
			if (status)
				fprintf(stderr, "Child process exited with non-zero code %d\n",
						status);
		}
		for (int j = 1; j < callsCount * 2 - 1; j++) {
			close(pipesArr[j]);
		}
	}
}