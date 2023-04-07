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
	int descCtoP[2];
	int result = pipe(descCtoP);
	if (result == -1) {
		printf("Unable to create pipe\n");
		return -1;
	}
	int descPtoC[2];
	result = pipe(descPtoC);
	if (result == -1) {
		printf("Unable to create pipe\n");
		return -1;
	}

	int pid;
	switch (pid = fork()) {
		case 0:
			close(descCtoP[1]);
			close(descPtoC[0]);
			int buff;
			for (int i = 0; i < count; i++) {
				read(descCtoP[0], &buff, 4);
				printf("Parent: %d\n", buff);

				buff *= 2;
				write(descPtoC[1], &buff, 4);
			}
			exit(EXIT_SUCCESS);
		case -1:
			printf("Unable to fork\n");
			exit(EXIT_FAILURE);
		default:
			close(descCtoP[0]);
			close(descPtoC[1]);
			for (int i = 0; i < 5 * count; i += 5) {
				write(descCtoP[1], &i, 4);

				read(descPtoC[0], &buff, 4);
				printf("Child: %d\n", buff);
			}
			exit(EXIT_SUCCESS);
	}
}