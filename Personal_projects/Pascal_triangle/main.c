#include <stdio.h>
#include <stdlib.h>
#include "Pascal.h" 


int main () 
{
	int i;
	printf("Enter the number of rows thet you want: \n");
	scanf("%d",&i);
	i = i + 2;
	int** rows = (int**)malloc(sizeof(int*)*(i));
	int* arr =  (int*)malloc(sizeof(int)+1);
	*arr = 1;
	int size = 0;
	int* pascal = triangle(i, size, rows);
	print_triangle(rows, i);
	free (rows);
	return 0;	
}
