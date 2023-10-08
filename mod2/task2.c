#include <stdio.h>

#define MAX(max, min)  \
	if (min > max) {    \
		int temp = max; \
		max = min;      \
		min = temp;     \
	}

typedef struct jar {
	int volume, amount;
} jar;

#define CHECKTARGET                                                            \
	if (max.amount == target || aver.amount == target || min.amount == target) \
		{\
	printf("Tranfusions count: %d\n", count);\
	return 0;\
	}

#define PRINT printf("%d %d %d\n", max.amount, aver.amount, min.amount);

void fill(jar* from, jar* to) {
	int free = to->volume - to->amount;
	int available = from->amount;
	MAX(free, available)
	from->amount -= available;
	to->amount += available;
}

int isEven(int first, int second) {
	MAX(first, second)
	for (int i = 2; i <= second; i++)
		if (first % i == 0 && second % i == 0) return 0;
	return 1;
}

int main() {
	jar max = {0, 0}, aver = {0, 0}, min = {0, 0};
	scanf("%d%d%d", &max.volume, &aver.volume, &min.volume);

	MAX(max.volume, aver.volume)
	MAX(aver.volume, min.volume)
	MAX(max.volume, aver.volume)

	int filled;
	scanf("%d", &filled);
	if (max.volume == filled) max.amount = filled;
	if (aver.volume == filled) aver.amount = filled;
	if (min.volume == filled) min.amount = filled;

	int target;
	scanf("%d", &target);

	if (isEven(aver.volume, min.volume) &&
		max.volume >= aver.volume + min.volume) {
		if (target > aver.volume) {
			printf("Unreachable amount of liquid\n");
			return -1;
		}
	}
	int count=0;
	//while (1) {
		 for (int i = 0; i < 100; i++) {
		fill(&max, &aver);
		count++;
		PRINT
		while (1) {
			fill(&aver, &min);
		count++;
			PRINT
			CHECKTARGET
			if (!aver.amount) break;
			fill(&min, &max);
		count++;
			PRINT
			CHECKTARGET
		}
	}
	printf("Time limit exceed\n");
}