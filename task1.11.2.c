#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *pipeName = "/tmp/pipename";
	int pipe;
	if (mkfifo(pipeName, 0777) != -1)
		fprintf(stderr, "Pipe created\n");
	else
		fprintf(stderr, "Pipe wasn't created; possibly already exist\n");

	if ((pipe = open(pipeName, O_RDONLY)) == -1) {
		fprintf(stderr, "Unable to open pipe\n");
		exit(EXIT_FAILURE);
	}

	int random;

	while (1) {
		if (read(pipe, &random, 4) == 4) printf("%d\n", random);
	}
}