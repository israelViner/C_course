#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Map_2.h"

int main()
{
	
    /* Question 1 part A */
    printf("\nQuestion 1 part A (Create a two dimensional array (in size of 2*5), fill it, print the max of each from the 5 sub-arrays, and sum the odd element of it):\n\n");
      
    int num_1[2][5];
	fill_array(*num_1);
	max_subarray(*num_1);
	int sum_odd = sum_odd_array(*num_1);
	printf("\nThe sum of the odd elements is: %d\n", sum_odd);
	

    /* Question 1 part A */
	printf("\nQuestion 1 part B (Check for a input number if is a prime number):\n\n");
	printf("Enter number that you want to check: ");
	float n;
	scanf("%f", &n);
	if (n != (int) n) {
			printf("The number isn't integer...");
			return 0;
	}
	is_prime((int)n);
	
    
    /* Question 2 */
    printf("\nQuestion 2 (Find the unique characters in string 1 - that do not exsist *in the same place* in string 2):\n\n");
    
	printf("Enter the the string 1:\n");
	char str1[ARRAY_SIZE] = {' '};
	scanf("%s", str1);
	
	printf("Enter the the string 2:\n");
	char str2[ARRAY_SIZE] = {' '};
	scanf("%s", str2);

	int string_length = 0;
	while ( str1[string_length] != '\0')
		string_length = string_length + 1;
	char new_str[string_length];
	
	squeeze(str1, str2, new_str);

	printf("\nThe unique string is: \n%s\n", new_str);
	

    /* Question 3 */
    printf("\nQuestion 3 (The Towers of Hanoi):\n\n");

    printf("Enter the number of disks: ");
    int a;
	scanf("%d", &a);
	
    /* Initiate call from source A to target C with auxiliary B */
    move(a, 'A', 'B', 'C');


    /* Question 5 */
    printf("\nQuestion 5 (Create list of lists):\n\n");

	printf("Enter number of lists for question 5: ");
	int b;
	scanf("%d", &b);
	int* len_of_arr = malloc(sizeof(int) * b);
	int** c = create_lists_of_list(b, len_of_arr);
	print_arrays(c, len_of_arr, b);
	clean_memory(c, b);

    return 0;
}