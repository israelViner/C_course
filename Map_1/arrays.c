#include <stdio.h>

#define ARRAY_SIZE 10

void reverse(int Array[ARRAY_SIZE]);


    
void insertionSort(int array[ARRAY_SIZE]) {
        int j;
        int i;
        int num;
        for (i = 1; i < ARRAY_SIZE; i++) {
          if (array[i] < array[i - 1]) {
            num = array[i];
            j = i - 1;
            while (j >= 0 && num < array[j]) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = num;
          }
        }
}



int main()
{
	int i, Array[ARRAY_SIZE];
	printf(" Enter elements into the Array :n ");
	for (i=0; i< ARRAY_SIZE ; i++)
	{
		printf("Enter %2d elements : ",i);
		scanf("%d",&Array[i]);
	}
	
	insertionSort(Array);
	printf("\n************************\n");
	printf(" here is the sort Array : \n ");
	for (i=0; i< ARRAY_SIZE ; i++)
	{
		printf("%4d",Array[i]);
	}
	
	reverse(Array);
	printf("\n************************\n");
	printf(" here is the reverse Array : \n ");
	for (i=0; i< ARRAY_SIZE ; i++)
	{
		printf("%4d",Array[i]);
	}
	
	printf("\n************************\n");
	return 0;
}


void reverse(int Array[ARRAY_SIZE])
{
	int temp,i;
	for (i=0; i < (ARRAY_SIZE/2) ; i++)
	{
		temp = Array[ARRAY_SIZE-1-i];
		Array[ARRAY_SIZE-1-i] = Array[i];
		Array[i] =temp;
	}
}
