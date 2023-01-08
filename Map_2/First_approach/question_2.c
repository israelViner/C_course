#include <stdio.h>

#define ARRAY_SIZE 10



/* Add the unique characters from the first string (that dosn't exsist in the second string) to the new string */
void squeeze(char *s1,char *s2, char *new_str)
{
	int new_loc = 0;
	int length_1 = 0;
	int string_length = 0;
	while ( s2[string_length] != '\0')
		string_length = string_length + 1;
	while ( s1[length_1] != '\0') {
		if (length_1 <= string_length)
			if (s1[length_1] != s2[length_1]) {
				new_str[new_loc] = s1[length_1];
				++new_loc;
			}		
		++length_1;
	}
	new_str[new_loc] = '\0';
}


int main() {
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

	printf("\n%s\n", new_str);
	
	return 0;
}
