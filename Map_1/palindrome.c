#include <stdio.h>

#define ARRAY_SIZE 10


/* Changing the upper letter to the lower */ 
char upper(char letter)
{
	if (letter >= 'A' && letter <= 'Z')
		letter += 32; 
	return letter;
}


/* The main task: checking if the string is palindrome - while ignoring differents bettween upper and lower letters & differents symbols from letters/numbers */
int isPalindrome(char str[], int n, int startFrom)
{
	int checkIfPalindrome = 1;
	while ((!(str[startFrom] >= '0' && str[startFrom] <= '9')) && (!(str[startFrom] >= 'a' && str[startFrom] <= 'z')) && (!(str[startFrom] >= 'A' && str[startFrom] <= 'Z')))
		startFrom++;
	while ((!(str[n] >= '0' && str[n] < '9')) && (!(str[n] >= 'a' && str[n] <= 'z')) && (!(str[n] >= 'A' && str[n] <= 'Z')))
		n--;
	
	if ((checkIfPalindrome) && (n >= startFrom))
	{
		str[startFrom] = upper(str[startFrom]);
		str[n] = upper(str[n]);
		if (str[startFrom] == str[n])
			checkIfPalindrome = isPalindrome(str, n - 1, startFrom + 1);
		else 
			checkIfPalindrome = 0;
	}
	return (checkIfPalindrome);
}


int main()
{
	printf("Enter the string:\n");
	char str[ARRAY_SIZE];
	scanf("%s", str);
	
	int string_length = 0;
	while ( str[string_length] != '\0') 
		string_length = string_length + 1;
	
     	int pass = isPalindrome(str, string_length-1, 0);
	printf("%d\n", pass);
	    
	return 0;
}

