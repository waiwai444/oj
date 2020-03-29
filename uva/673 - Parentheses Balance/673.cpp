#include <stdio.h>

int main()
{
	int n, i;
	char seq[130];
	char stack[130];
	int top;
	scanf("%d", &n);
	fgets(seq, 130, stdin);
	while(n--)
	{
		fgets(seq, 130, stdin);
		top = 0;
		for(i = 0; seq[i] != '\n' && seq[i] != '\0'; i++)
		{
			if(seq[i] == '(')
				stack[top++] = '(';
			else if(seq[i] == ')')
			{
				if(top > 0 && stack[top-1] == '(')
					top--;
				else
				{
					top = -1;
					break;
				}
			}
			else if(seq[i] == '[')
				stack[top++] = '[';
			else
			{
				if(top > 0 && stack[top-1] == '[')
					top--;
				else
				{
					top = -1;
					break;
				}
			}
		}
		if(top == 0)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
