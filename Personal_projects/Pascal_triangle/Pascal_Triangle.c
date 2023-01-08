#include <stdio.h>
#include <stdlib.h>
#include "Pascal.h" 


/* Print the the triangle */
void print_triangle(int** rows, int n)
{
	for (int row = 0; row < n; row++)
	{
		for (int i = 0; i< (n/2)-(row/2); i++)
			printf("       ");
		if (row%2 == 0)
			printf("    ");
		for (int i = 0; i< row-1 ; i++)
			printf("%8d",*(*(rows + row) + i));
		printf("\n");
		free(*(rows + row));	
	}
}


/* Calculate the Pascal-triangle for each row recursively */
int* triangle(int n, int size,  int** rows)
{
	int* row = (int*)malloc(sizeof(int)*(size+1));
	int* prev_row = *(rows + (size - 1));
	if (size != n)
	{
		*row = 1;
		for (int i = 1; i < size-1; ++i)
		{
			*(row + i) = *(prev_row + (i - 1)) + *(prev_row + i);
		}
		*(row + size) = 1;
		*(rows + size) = row;
		triangle(n, size + 1, rows);
	}
	return row;
}


