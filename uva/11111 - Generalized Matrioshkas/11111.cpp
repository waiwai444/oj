#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int matr_stack[1000];
int top;
int cap_stack[1000];	// capability

char input[30000];

int main()
{
	int n;
	char *ptr;
	bool is_matr;
	while(fgets(input, 30000, stdin))
	{
		top = -1;
		is_matr = true;
		n = atoi(strtok(input, " "));
		if(n > 0)
			is_matr = false;
		else
		{
			++top;
			matr_stack[top] = cap_stack[top] = n;
			while(top >= 0)
			{
				ptr = strtok(NULL, " ");
				if(ptr == NULL)
				{
					is_matr = false;
					break;
				}
				n = atoi(ptr);
				if(n < 0)
				{
					if(n <= cap_stack[top])
					{
						is_matr = false;
						break;
					}
					else
					{
						cap_stack[top] -= n;
						++top;
						matr_stack[top] = cap_stack[top] = n;						
					}
				}
				else
				{
					if(-n != matr_stack[top])
					{
						is_matr = false;
						break;
					}
					else
					{
						--top;
					}
				}
			}
			if(strtok(NULL, " ") != NULL)
				is_matr = false;
		}
		if(is_matr)
			printf(":-) Matrioshka!\n");
		else
			printf(":-( Try again.\n");
	}
	return 0;
}
