#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Find the max element in each from the 5 sub-arrays */
void max_subarray(int* arr)
{
	printf("\nThe max elements in the sub-arrays:\n");
	for (int i = 0; i <= 8; i+=2) {
		if (*(arr + i) > *(arr+i+1))
			printf("%d, ", *(arr+i));
		else
			printf("%d, ", *(arr+i+1));
	}
	printf("\n");
}


/* Sum the odd elements in the array */
int sum_odd_array(int* arr)
{
	int sum_odd = 0;
	for (int i = 0; i < 10; i++)
		if (*(arr + i)%2 == 1)
			sum_odd += *(arr + i);
	return sum_odd;
}


/* Fill the array with 10 integer's input */
void fill_array( int* arr)
{
	int k;
	for (int j = 0; j < 10; ++j)
	{
		printf("Enter the element %d for the array: ", j+1);
		scanf("%d", &k);
		*(arr + j) = k;
	}
}


/* Check if the number is a prime number */
void is_prime(int n)
{
	//double sq = sqrt(n);
	for(int i = 2; i<= n/2; ++i)
	{
		if (n/i == (float) n/i) {
			printf("\nThe number %d isn't prime number\n", n);
			return;
		}
	}
	printf("\nThis number %d is prime number!!\n", n);
	return;
}	