#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int initGame(int* intentedNum, int* attempts);

void main() {
	srand(time(NULL));

	int money;

	printf("Внесите деньги на счёт (курс 2:3)\n> ");
	scanf("%d", &money);
	while (money < 10) {
		printf("Минимальная сумма взноса - 10 монет\n> ");
		scanf("%d", &money);
	}

	money = money / 2 * 3;

	int playAgain = 0;
	do {
		printf("Очков на счёте: %d\n\n", money);

		int bet;
		printf("Сделайте ставку!\n> ");
		scanf("%d", &bet);
		while (bet > money || bet <= 0) {
			printf(
				"Ставка должна быть больше нуля и не превосходить ваш "
				"счёт\n> ");
			scanf("%d", &bet);
		}

		int intentedNum, attempts;
		initGame(&intentedNum, &attempts);

		while (attempts > 0) {
			printf("\tОсталось %d попыток\n> ", attempts);
			int num;
			scanf("%d", &num);
			if (num > intentedNum)
				printf("Введённое число больше загаданного\n");
			if (num < intentedNum)
				printf("Введённое число меньше загаданного\n");
			if (num == intentedNum) break;
			attempts--;
		}
		if (attempts > 0) {
			printf("Вы угадали!\n");
			money += bet;
		} else {
			printf("Вы не смогли угадать; ваши попытки кончились\n");
			money -= bet;
		}

		if (money <= 0) {
			printf("У вас закончились деньги на счету - вы проиграли\n");
			playAgain = 0;
		} else {
			while (getchar() != '\n')
				;

			printf("Хотите сыграть ещё?\n");
			playAgain = getchar() == 208;
			while (getchar() != '\n')
				;
		}

	} while (playAgain);
}

int initGame(int* intentedNum, int* attempts) {
	int low, high;

	printf("Введите нижнюю границу\n> ");
	scanf("%d", &low);
	printf("Нижняя граница: %d\n", low);
	printf("Введите верхнюю границу\n> ");
	scanf("%d", &high);
	while (low >= high) {
		printf(
			"Верхняя граница должна быть больше нижней границы. Повторите "
			"ввод\n> ");
		scanf("%d", &high);
	}
	printf("Верхняя границы: %d\n\n", high);

	*intentedNum = rand() % (high - low + 1) + low;

	printf("Введите количество попыток ввода\n> ");
	scanf("%d", attempts);
	while (attempts < 1) {
		printf("Должна быть хотя бы одна попытка. Повторите ввод\n> ");
		scanf("%d", attempts);
	}
	printf("Количество попыток ввода: %d\n", *attempts);
}