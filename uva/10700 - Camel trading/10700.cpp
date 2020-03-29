#include <stdio.h>

int parse_int(char **str)
{
	int n = 0;
	while(**str >= '0' && **str <= '9')
	{
		n = 10*n+**str-'0';
		(*str)++;
	}
	return n;
}

long long nstack[2];
int nstack_top;
char prev_op;

long long get_min(char line[])
{
	int n;
	char op, *p = line;
	nstack[0] = parse_int(&p);
	nstack_top = 0;
	prev_op = '\0';
	while(*p != '\n' && *p != '\0')
	{
		op = *(p++);
		n = parse_int(&p);
		if(op == '*')
			nstack[nstack_top] *= n;
		else if(op == '+')
		{
			if(prev_op == '+')
			{
				nstack[nstack_top-1] += nstack[nstack_top];
				nstack[nstack_top] = n;
			}
			else
			{
				prev_op = '+';
				nstack[++nstack_top] = n;
			}
		}
	}
	if(prev_op == '+')
		nstack[0] += nstack[1];
	return nstack[0];
}

long long get_max(char line[])
{
	int n;
	char op, *p = line;
	nstack[0] = parse_int(&p);
	nstack_top = 0;
	prev_op = '\0';
	while(*p != '\n' && *p != '\0')
	{
		op = *(p++);
		n = parse_int(&p);
		if(op == '+')
			nstack[nstack_top] += n;
		else if(op == '*')
		{
			if(prev_op == '*')
			{
				nstack[nstack_top-1] *= nstack[nstack_top];
				nstack[nstack_top] = n;
			}
			else
			{
				prev_op = '*';
				nstack[++nstack_top] = n;
			}
		}
	}
	if(prev_op == '*')
		nstack[0] *= nstack[1];
	return nstack[0];
}

int main()
{
	int n;
	char line[50];
	scanf("%d", &n);
	fgets(line, sizeof(line), stdin);
	while(n--)
	{
		fgets(line, sizeof(line), stdin);
		printf("The maximum and minimum are %lld and %lld.\n", get_max(line), get_min(line));
	}
	return 0;
}