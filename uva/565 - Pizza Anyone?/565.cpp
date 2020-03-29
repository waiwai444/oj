#include <stdio.h>
#include <string.h>

#define OMIT 0
#define INCL 1
#define ANY 2

bool constraint_flag[16][2];
char requirement[12][16];
int people_num;
bool toppings[16];

bool satisfied()
{
	int i, j;
	for(i = 0; i < people_num; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(requirement[i][j] == OMIT && !toppings[j])
				break;
			if(requirement[i][j] == INCL && toppings[j])
				break;
		}
		if(j == 16)
			return false;
	}
	return true;
}

bool backtrack(char cur)
{
	if(cur > 'P')
		return satisfied();
	
	char idx = cur-'A';
	
	if(!constraint_flag[idx][0] && !constraint_flag[idx][1])
		return backtrack(cur+1);
	
	if(constraint_flag[idx][0])
	{
		if(backtrack(cur+1))
			return true;
	}
	
	if(constraint_flag[idx][1])
	{
		toppings[idx] = true;
		if(backtrack(cur+1))
			return true;
		toppings[idx] = false;
	}
    
	return false;
}

int main()
{
	int i;
	char input[40], *ptr;
	while(scanf("%s", input) != EOF)
	{
		memset(constraint_flag, false, sizeof(constraint_flag));
		memset(requirement, ANY, sizeof(requirement));
		memset(toppings, false, sizeof(toppings));
		people_num = 0;
		do
		{
			for(ptr = input; *ptr != ';'; ptr += 2)
			{
				if(*ptr == '+')
				{
					requirement[people_num][ptr[1]-'A'] = INCL;
					constraint_flag[ptr[1]-'A'][INCL] = true;
				}
				else
				{
					requirement[people_num][ptr[1]-'A'] = OMIT;
					constraint_flag[ptr[1]-'A'][OMIT] = true;
				}
			}
			people_num++;
			scanf("%s", input);
		} while(input[0] != '.');
		
		if(backtrack('A'))
		{
			printf("Toppings: ");
			for(i = 0; i < 16; i++)
			{
				if(toppings[i])
				{
					printf("%c", 'A'+i);
				}
			}
			printf("\n");
		}
		else
		{
			printf("No pizza can satisfy these requests.\n");
		}
	}
	return 0;
}