#include <stdio.h> 
#include <limits.h>
#include "arrays.h"


/* Finding the maximum possible product between 2 elements in an array  */
int find_max_product(int* arr, int n) {
    int max_1, max_2, min_1, min_2;
    
    max_1 = max_2 = INT_MIN;
    min_1 = min_2 = INT_MAX; 

    for (int i = 0; i < n; ++i) {
        if (*(arr + i) > max_1) {
            max_2 = max_1;
            max_1 = *(arr + i);
        }
        else if (*(arr + i) > max_2)
            max_2 = *(arr + i);
        if (*(arr + i) < min_1) { 
            min_2 = min_1;
            min_1 = *(arr + i);
        }
        else if (*(arr + i) < min_2)
            min_2 = *(arr + i);
    }
    printf("The minimum's of the array them: %d, %d\n", min_1, min_2);
    printf("The maximum's of the array them: %d, %d\n", max_1, max_2);

    if (max_1 * max_2 > min_1 * min_2)
        return max_1 * max_2;
    else
        return min_1 * min_2;
}


/* Finding the element that divides an array (that is the sum of the elements to his right end left is equal) */
int find_divides_element(int* array, int n) {
    int head, tail;
    int sum_head = 0, sum_tail = 0;
    head = 0;
    tail = n-1;
    sum_head = *(array + head);
    sum_tail = *(array + tail);
    while (tail > head + 2) {
        if (sum_head > sum_tail) {
            --tail;
            sum_tail += *(array + tail);
        }
        else {
            ++head;
            sum_head += *(array + head);
        }
    }
    if (sum_head == sum_tail)
        return *(array + head + 1);
    else 
        return INT_MIN;        
}
