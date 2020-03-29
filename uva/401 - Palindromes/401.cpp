#include <stdio.h>
#include <string.h>

bool is_reversed(char ch1, char ch2)
{
	if(ch1 == ch2 && (ch1 == 'A' || ch1 == 'H' || ch1 == 'I' || ch1 == 'M' || ch1 == 'O' || ch1 == 'T' || ch1 == 'U' || ch1 == 'V' || ch1 == 'W' || ch1 == 'X' || ch1 == 'Y' || ch1 == '1' || ch1 == '8'))
		return true;
	if(ch1 == 'E' && ch2 == '3' || ch1 == '3' && ch2 == 'E' || 
		ch1 == 'J' && ch2 == 'L' || ch1 == 'L' && ch2 == 'J' ||
		ch1 == 'S' && ch2 == '2' || ch1 == '2' && ch2 == 'S' ||
		ch1 == 'Z' && ch2 == '5' || ch1 == '5' && ch2 == 'Z')
		return true;
	return false;
}

int main()
{
	int i, len;
	char str[21];
	bool palindrome, mirrored;
	while(scanf("%s", str) != EOF)
	{
		palindrome = mirrored = true;
		len = strlen(str);
		int temp = (len+1)/2;
		for(i = 0; i < temp; i++)
		{
			if(palindrome && str[i] != str[len-i-1])
				palindrome = false;
			if(mirrored && !is_reversed(str[i], str[len-i-1]))
				mirrored = false;
			if(!palindrome && !mirrored)
				break;
		}
		if(palindrome)
		{
			if(mirrored)
				printf("%s -- is a mirrored palindrome.\n\n", str);
			else
				printf("%s -- is a regular palindrome.\n\n", str);
		}
		else
		{
			if(mirrored)
				printf("%s -- is a mirrored string.\n\n", str);
			else
				printf("%s -- is not a palindrome.\n\n", str);
		}
	}
	return 0;
}
