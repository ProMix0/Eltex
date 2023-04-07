#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Invalid arguments count\n");
		return -1;
	}

	int file = open(argv[1], 0);
	if (file == -1) {
		printf("Error opening file %s\n", argv[1]);
		return -1;
	}
	char buff[64];
	int readed = read(file, buff, 63);
	while (readed) {
		buff[readed] = 0;
		printf("%s", buff);
		readed = read(file, buff, 63);
	}
	close(file);
}