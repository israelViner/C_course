#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "SubArrays.h"




/* Comaring between two arrays (and return 1 if they're eaqual) */
int compareArrays(int* a, int* b, int n) {
    int count = 0;
    while (*(b + count) != 0)
        ++count;
    int arr_size = count+1; 
    if (arr_size != n)
        return 0;
    for(int i = 0; i < n-1; i++) {
        if (a[i] != b[i])
            return 0;
        }
    return 1;
}


/* Cecking if an array is exsist in the list of arrays */
int is_exsist(int* array,  int** list_of_lists, int n) {
    int i = 0;
    while (i < pow(2,N) && *(list_of_lists + i) != 0) {
        if (compareArrays(array, *(list_of_lists + i), n))
            return 1;
        ++i;
    }
    return 0;
}


/* Inserting an array to the list of the arrays */
void insert(int* array,  int** list_of_lists) {
    int i = 0;
    while (i < pow(2,N) && *(list_of_lists + i) != 0)
        ++i;
    if (i < pow(2,N))
        *(list_of_lists + i) = array;
}


/* The main function - receiving an array and finding recursively all of the sub-arrays that can be created from it */
void sub_arrays(int* array, int n, int** list_of_lists)
{
    /* Stop condition */
    if (n == 0) {
        int* new_array =(int*)calloc(2, sizeof(int));
        *new_array = -214735;
        if (!is_exsist(new_array, list_of_lists, 2))
            insert(new_array, list_of_lists);
        else
            free(new_array);
        return;
    }
    
    /* Insert the array (plus 0 at the end) into the list of the arrays - if it isn't there yet */
    int* new_array1 =(int*)calloc(n+1, sizeof(int));
    int j = 0;
    for (j; j < n; ++j) 
        *(new_array1 + j) = *(array + j);
    if (!is_exsist(new_array1, list_of_lists, n+1)) 
        insert(new_array1, list_of_lists);
    else
        free(new_array1);    
   
    /* Create n sub arrays in n-1 size - and call recursively to the function for each one of them */    
    for (int i = 0; i < n; ++i) {
        int* new_array =(int*)calloc(n-1, sizeof(int));
        int k = 0;
        int j = 0;
        for (j; j < n; ++j) {
            if (j != i) 
                *(new_array + j - k) = *(array + j);
            else 
                ++k;
        }
        if (!is_exsist(new_array, list_of_lists, n)) {
            sub_arrays(new_array, n-1, list_of_lists);              
        } 
    }
}


/* Print the the list of lists (and free the list later) */
void print_list(int** list_of_lists)
{
	for (int j = 0; j < pow(2,N); ++j)
	{
        int i = 0;
		while (*(*(list_of_lists + j) + i) != 0) {
     		printf("%d, ",*(*(list_of_lists + j) + i));
            ++i;
        }
		printf("\n");
		free(*(list_of_lists + j));	
	}
    free(list_of_lists);	
}

