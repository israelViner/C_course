#include <stdio.h>
#include <stdlib.h>


/* Swap two variables using their pointers */
void swap(int **a, int **b) {
	int *tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


int main() {
	int arr_a[6] = {5,3,2,6};
	int arr_b[6] = {6,9,2,5,7,3};
	int* a = arr_a;
	int* b = arr_b;
	
	for (int i = 0; i < 4; i++) {
		printf("%d \t", *(a+i));
	}
	printf("\n");
	for (int j = 0; j < 6; j++) {
                printf("%d \t", *(b+j));
        }
	printf("\n\n\n");

	swap(&a, &b);

	for (int i = 0; i < 6; i++) {
                printf("%d \t", *(a+i));
        }
	printf("\n");
        for (int j = 0; j < 4; j++) {
                printf("%d \t", *(b+j));
        }
	printf("\n");


}
	
