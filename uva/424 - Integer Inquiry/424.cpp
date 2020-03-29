#include <stdio.h>
#include <string.h>

int main()
{
	char input[105], sum[103];
	int i, j, len, carry;
	const int last = 101;
	memset(sum, 0, sizeof(sum));
	while(fgets(input, sizeof(input), stdin))
	{
		input[strlen(input)-1] = 0;
		if(input[0] == '0' && input[1] == '\0')
			break;
		len = strlen(input);
		for(i = 0; i < len; i++)
			input[i] -= '0';
		carry = 0;
		for(i = len-1, j = last; i >= 0; i--, j--)
		{
			sum[j] += input[i]+carry;
			if(sum[j] >= 10)
			{
				sum[j] -= 10;
				carry = 1;
			}
			else
				carry = 0;
		}
		if(carry != 0)
		{
			while(j >= 0)
			{
				sum[j] += carry;
				if(sum[j] >= 10)
				{
					sum[j] -= 10;
					carry = 1;
				}
				else
					break;
				j--;
			}
		}
	}
	for(i = 0; i <= last; i++)
		if(sum[i] != 0)
			break;
	for(j = i; j <= last; j++)
		sum[j] += '0';
	printf("%s\n", sum+i);
	return 0;
}
