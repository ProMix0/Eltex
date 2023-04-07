#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid arguments count\n");
		return -1;
	}

	FILE* file = fopen(argv[1], "a");
	if (file == 0) {
		printf("Error opening file %s\n", argv[1]);
		return -1;
	}
	char buff[64];
	scanf("%s", buff);
	int len = strlen(buff);
	int result = fwrite(buff, len, 1, file);
	if (result == -1) {
		printf("Error writing file\n");
		printf("%x %d\n", buff, result);
		return -1;
	}
	fclose(file);
}