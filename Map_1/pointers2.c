#include <stdio.h>
	

void sum_difference(int *a, int *b) {
	int tmp = *a;
	*a = *a + *b;
	if (*b < tmp)
		*b = tmp - *b;
	else
		*b = *b - tmp;
}


int main() {
	int a = 8;
	int b = 15;

	sum_difference(&a, &b);
	
	printf("The sum of the numbers is: %d, and the difference is: %d\n", a, b);
}
