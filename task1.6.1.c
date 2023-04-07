#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Invalid arguments count\n");
		return -1;
	}

	int file = open(argv[1], O_APPEND | O_WRONLY);
	if (file == -1) {
		printf("Error opening file %s\n", argv[1]);
		return -1;
	}
	char buff[64];
	scanf("%s", buff);
	int len = strlen(buff);
	int result = write(file, buff, len);
	if (result == -1) {
		printf("Error writing file\n");
		printf("%x %d\n", buff, result);
		return -1;
	}
	close(file);
}