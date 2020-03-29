#include <stdio.h>

#define MAT_TOKEN 'M'

struct matrix_dim
{
	int r, c;
};

int n;
matrix_dim mat[26];
char token_stack[500];
int token_top;
matrix_dim dim_stack[500];
int dim_top;

bool mul(matrix_dim mat, int *sum)	// multiply the top of the stack with mat
{
	if(dim_stack[dim_top-1].c != mat.r)
		return false;
	*sum += dim_stack[dim_top-1].r*dim_stack[dim_top-1].c*mat.c;
	token_stack[token_top-1] = MAT_TOKEN;
	dim_stack[dim_top-1].c = mat.c;
	return true;
}

int main()
{
	int i, r, c;
	char input[500];
	int sum;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%s%d%d", input, &r, &c);
		mat[input[0]-'A'].r = r;
		mat[input[0]-'A'].c = c;
	}
	fgets(input, 500, stdin);
	while(fgets(input, 500, stdin))
	{
		dim_top = token_top = sum = 0;
		for(i = 0; input[i] != '\0' && input[i] != '\n'; i++)
		{
			if(input[i] >= 'A' && input[i] <= 'Z')
			{
				if(token_top == 0 || token_stack[token_top-1] == '(')
				{
					token_stack[token_top++] = MAT_TOKEN;
					dim_stack[dim_top++] = mat[input[i]-'A'];
				}
				else if(token_stack[token_top-1] == MAT_TOKEN)
				{
					if(!mul(mat[input[i]-'A'], &sum))
						goto error;
				}
				
			}
			else if(input[i] == '(')
			{
				token_stack[token_top++] = '(';
			}
			else	// ')'
			{
				token_top -= 2;
				if(token_top > 0 && token_stack[token_top-1] == MAT_TOKEN)
				{
					dim_top--;
					if(!mul(dim_stack[dim_top], &sum))
						goto error;
				}
				else
					token_stack[token_top++] = MAT_TOKEN;
			}
		}
		printf("%d\n", sum);
		continue;
error:
		printf("error\n");
	}
	return 0;
}
