#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 40
int MAX = 1000000;
int arr[SIZE];
time_t t1;


/* Create an array in SIZE's length. and fill it with random numbers */
void init() {
	int i;
	srand((unsigned) time(&t1));
	for(i=0; i<SIZE; ++i)
		arr[i] = random()%SIZE+1;
}


/* Printing the array */
void printArray() {
	int i;	
	for(i=0; i<SIZE; ++i)
		printf("%d, ",arr[i]);
	printf("\n");
}


/* Choose the pivot index */
int choose_pivot(int start, int end)
{
	srand(time(0));
	return ((rand() % (end - start + 1)));
}


/* The partition process */
int partition(int start, int end, int pivot_element, int count) {
	
	/* Find The number of the smaellers elements */
	int sizeLeftArray = 0;
	for (int j = start; j < end + 1; j++) {
		if (arr[j] < pivot_element)
			sizeLeftArray = sizeLeftArray + 1;
	}
	
	/* Create an auxiliary arrays and fill them in -1 */
	int left_array[SIZE], right_array[SIZE];
	for(int c = 0; c<SIZE; ++c) {
		left_array[c] = -1;
		right_array[c] = -1;
	}

	/* Fill the auxiliary arrays with the biggers/smallers elments */
	int x = 0, y = 0;
	for (int i = start; i <= end; i++) {
		if (arr[i] < pivot_element) {
			left_array[x] = arr[i];
			x++;
		}
		else if (arr[i] > pivot_element) 
		{
			right_array[y] = arr[i];
			y++;
		}
	}
	
	/* Return the elements to the array: first the smaller elements, than the pivots and finally the bigger part */ 
	int z = start;
	int f = 0;
	while (left_array[f] != -1) {
		arr[z] = left_array[f];
		++f;
		++z;
	}
	int middle = 0;
	while (middle < count) {
		arr[z] = pivot_element;
		++z;
		++middle;
	}
	f = 0;
	while (right_array[f] != -1) {
		arr[z] = right_array[f];
		++f;
		++z;
	}
	return sizeLeftArray;
}


/* The main function of the sort */
void quick_sort(int start, int end)
{

/* Stop condition */
if ((end - start) <= 1) {
	return;
}
else {
	/* Determine the pivot index & the keep the value of the pivot element */
	int pivot = choose_pivot(start, end);
	int pivot_element = arr[pivot + start];
	
	/* Count the number of the appearances of the pivot elements */
	int count = 0;
	for (int j = start; j < end + 1; j++) {
		if (arr[j] == pivot_element)
			++count;
	}	

	/* Call to the partition around to the pivot element */ 
	int sizeLeftArray = partition(start, end, pivot_element, count);

	/* The recursion calls on the smaller and bigger parts of the array */
	quick_sort(start, (start + sizeLeftArray - 1));
	quick_sort((start + sizeLeftArray + count), end);
	
	}
}


int main() {
	init();
	printArray(); 
	quick_sort(0, SIZE -1);
	printArray(); 
}
