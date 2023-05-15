#include <stdio.h>

extern int f1(int a);
extern int f2(int a);

void main() {
	int a;
	scanf("%d", &a);
	printf("%d^3=%d\n", a, f1(a));
	printf("%d^4=%d\n", a, f2(a));
}