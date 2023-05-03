#include <stdio.h>

#define SWAP(max, min)  \
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
		return 0;

#define PRINT printf("%d %d %d\n", max.amount, aver.amount, min.amount);

void fill(jar* from, jar* to) {
	int free = to->volume - to->amount;
	int available = from->amount;
	SWAP(free, available)
	from->amount -= available;
	to->amount += available;
}

int isEven(int first, int second) {
	SWAP(first, second)
	for (int i = 2; i <= second; i++)
		if (first % i == 0 && second % i == 0) return 0;
	return 1;
}

int main() {
	jar max = {0, 0}, aver = {0, 0}, min = {0, 0};
	scanf("%d%d%d", &max.volume, &aver.volume, &min.volume);

	SWAP(max.volume, aver.volume)
	SWAP(aver.volume, min.volume)
	SWAP(max.volume, aver.volume)

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
	while (1) {
		// for (int i = 0; i < 25; i++) {
		fill(&max, &aver);
		PRINT
		while (1) {
			fill(&aver, &min);
			PRINT
			CHECKTARGET
			if (!aver.amount) break;
			fill(&min, &max);
			PRINT
			CHECKTARGET
		}
	}
}