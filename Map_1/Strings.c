#include <stdio.h>


#define False 1
#define True 0 
#define ARRAY_SIZE 10

/*void reverse (char s[ ] )

{
	int string_length;
	int i;
	char tmp;

	string_length = 0;
	while ( s[string_length] != '\0')
		string_length = string_length + 1;

	for (i = 0; i < string_length/2; i++)
	{
		tmp = s[i];
		s[i] = s[string_length - i - 1];
		s[string_length i 1] = tmp;
	}
}*/

int is_strong(char s[])
{
	int string_length;
	int capital = False; 
	int sign = False;
	int number = False;
			
	string_length = 0;
	while ( s[string_length] != '\0')
	{
		if (s[string_length] >= '0' && s[string_length] <= '9')
			number = True;
		else if (s[string_length] >= 'A' && s[string_length] <= 'B')
			capital = True;
		else if (s[string_length] == '!' || s[string_length] == '%' || s[string_length] == '#' || s[string_length] == '@')
			sign = True;
			
		++string_length;
	}
	
	//printf("i = %d len: %d\n", s[string_length], string_length); 
	if (string_length < 5)
		return False;
	else if (capital == True && sign == True && number == True)
		return True;
	else 
		return False;
		
}




void expand(char s[])
{

	int string_length = 0;

	while ( s[string_length] != '\0') 
		string_length = string_length + 1;
	if (s[1] == '-' && string_length == 3)
	{	
		for (char i = s[0]; i <= s[2]; ++i)
			if ((i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
				printf("%c, ", i);
	}
	printf("\n");
}



int main()
{
	printf("A:\n");
	char str[ARRAY_SIZE] = {' '};
	scanf("%s", str);
	
     //The first task
	int pass = is_strong(str);
	printf("%d\n", pass);
	
     //The second task
     	printf("B:\n");
     	char str2[ARRAY_SIZE];
	scanf("%s", str2);
	expand(str2);
	
	return 0;
}



