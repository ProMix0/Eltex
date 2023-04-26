#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Invalid arguments count\n");
		return -1;
	}

	int count = atoi(argv[1]);
	int desc[2];
	int result = pipe(desc);
	if (result == -1) {
		printf("Unable to create pipe\n");
		return -1;
	}

	int pid;
	switch (pid = fork()) {
		case 0:
			close(desc[1]);
			int buff;
			for (int i = 0; i < count; i++) {
				read(desc[0], &buff, 4);
				printf("%d\n", buff);
			}
			exit(EXIT_SUCCESS);
		case -1:
			printf("Unable to fork\n");
			exit(EXIT_FAILURE);
		default:
			close(desc[0]);
			for (int i = 0; i < 5 * count; i += 5) {
				write(desc[1], &i, 4);
			}
			exit(EXIT_SUCCESS);
	}
}