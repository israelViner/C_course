#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void max_subarray(int* arr)
{
	for (int i = 0; i <= 8; i+=2) {
		if (*(arr + i) > *(arr+i+1))
			printf("%d\t", *(arr+i));
		else
			printf("%d\t", *(arr+i+1));
	}
	printf("\n");
}


int sum_odd_array(int* arr)
{
	int sum_odd = 0;
	for (int i = 0; i < 10; i++)
		if (*(arr + i)%2 == 1)
			sum_odd += *(arr + i);
	return sum_odd;

}


void fill_array( int* arr)
{
	int k;
	for (int j = 0; j < 10; ++j)
	{
		printf("Enter the element %d: ", j+1);
		scanf("%d", &k);
		*(arr + j) = k;
	}
}


void is_prime(int n)
{
	//double sq = sqrt(n);
	for(int i = 2; i<= n/2; ++i)
	{
		if (n/i == (float) n/i) {
			printf("This number isn't prime number\n");
			return;
		}
	}
	printf("This number is prime number!!\n");
	return;
}	
	

int main()
{
	int num[2][5];
	fill_array(*num);
	max_subarray(*num);
	int sum_odd = sum_odd_array(*num);
	printf("The sum of the odd elements is: %d\n", sum_odd);
	
	printf("Enter number that you want to check: ");
	float n;
	scanf("%f", &n);
	if (n != (int) n) {
			printf("The number isn't integer...");
			return 0;
	}
	is_prime((int)n);
	return 0;
}
