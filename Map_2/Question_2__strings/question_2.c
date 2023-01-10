#include <stdio.h>


/* Add the unique characters from the first string (that do not exsist *in the same place* second string) to the new string */
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