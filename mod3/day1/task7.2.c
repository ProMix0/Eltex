#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid arguments count\n");
		return -1;
	}

	FILE* file = fopen(argv[1], "r");
	if (file == 0) {
		printf("Error opening file %s\n", argv[1]);
		return -1;
	}
	char buff[64];
	int readed = fread(buff, 1, 63, file);
	printf("Readed: %d\n", readed);
	while (readed) {
		buff[readed] = 0;
		printf("%s", buff);
		readed = fread(buff, 1, 63, file);
	}
	fclose(file);
}