#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "SubArrays.h"


int main() {
        int n = N;
        int arr[N] = {3,8,5,6};
        int* array = arr;
        int size = pow(2, N);
        int** list_of_lists = (int**)calloc(size, sizeof(int*));
        sub_arrays(array, n, list_of_lists);
        print_list(list_of_lists);
        return 0;
}
