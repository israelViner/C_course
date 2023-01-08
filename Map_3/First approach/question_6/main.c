#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "arrays.h"

int main() {

    /* The first task - finding the largest possible product between 2 elements in the array  */
    int arr[] = {-35, -50, 74, 20, 15};
    int max_pro = find_max_product(arr, 5);
    printf("The max product of the array is: %d\n", max_pro);

    /* The second task - finding the element that divides an array */
    int array[] = {11, 5, 9, 8, 2, 6};
    int divides = find_divides_element(array, 6);
    if (divides != INT_MIN)
        printf("The divides element is: %d\n", divides);
    else 
        printf("There is no divides element for this array\n");
    
    return 0;

}