#include <stdio.h>
#include <string.h>

int main()
{
	int i, idx;
	char expr[120];
	int var[26];
	bool used[26];
	int result;
	char b_op, pre_u_op;
	while(fgets(expr, sizeof(expr), stdin))
	{
		expr[strlen(expr)-1] = 0;
		for(i = 0; i < 26; i++)
			var[i] = i+1;
		memset(used, false, sizeof(used));
		result = 0;
		b_op = '+';
		pre_u_op = 0;
		i = 0;
		while(expr[i] != '\0')
		{
			while(expr[i] == ' ')
				i++;
			if(expr[i] == '\0')
				break;
			if(expr[i] >= 'a' && expr[i] <= 'z')
			{
				idx = expr[i]-'a';
				used[idx] = true;
				if(pre_u_op == '+')
					var[idx]++;
				else if(pre_u_op == '-')
					var[idx]--;
				pre_u_op = 0;
				if(b_op == '+')
					result += var[idx];
				else
					result -= var[idx];
				i++;
				while(expr[i] == ' ')
					i++;
				if(expr[i] == '\0')
					break;
				if(expr[i] == '+' && expr[i+1] == '+')
				{
					var[idx]++;
					i = i+2;
				}
				else if(expr[i] == '-' && expr[i+1] == '-')
				{
					var[idx]--;
					i = i+2;
				}
			}
			else if(expr[i] != expr[i+1])	// expr[i] == +' or '-'
				b_op = expr[i++];
			else
			{
				pre_u_op = expr[i];
				i += 2;
			}
		}
		printf("Expression: %s\n    value = %d\n", expr, result);
		for(i = 0; i < 26; i++)
		{
			if(used[i])
			{
				printf("    %c = %d\n", i+'a', var[i]);
			}
		}
	}
	return 0;
}
