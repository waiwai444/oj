#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND 0
#define FOUND 1
#define NONE 2

char stack[10000];
int top;
char input[10000];
void read_expr(char *expr)
{
	int i;
	char *ptr = expr;
	top = 0;	
	do
	{
		scanf("%s", input);
		strcpy(ptr, input);
		ptr += strlen(input);
		for(i = 0; input[i] != '\0'; i++)
			if(input[i] == '(')
				stack[top++] = '(';
			else if(input[i] == ')')
				top--;
	} while(top > 0);	
}

int traverse(char **expr_ptr, int cur_sum, int n)
{
	if(**expr_ptr == ')')
	{
		(*expr_ptr)++;
		return NONE;
	}
	char *ptr;
	int value = strtol(*expr_ptr, &ptr, 10);
	*expr_ptr = ptr;
	cur_sum += value;
	(*expr_ptr)++;
	int ret1, ret2;
	if((ret1 = traverse(expr_ptr, cur_sum, n)) == FOUND)
		return FOUND;
	(*expr_ptr)++;
	if((ret2 = traverse(expr_ptr, cur_sum, n)) == FOUND)
		return FOUND;
	(*expr_ptr)++;
	if(ret1 == NONE && ret2 == NONE && cur_sum == n)
		return FOUND;
	return NOT_FOUND;
}

int main()
{
	int n;
	char expr[20000], *ptr;
	while(scanf("%d", &n) != EOF)
	{
		read_expr(expr);
		ptr = &expr[1];
		if(traverse(&ptr, 0, n) == FOUND)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}