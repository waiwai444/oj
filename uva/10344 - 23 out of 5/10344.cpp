#include <stdio.h>
#include <string.h>
#include <algorithm>

int numbers[5];
char ops[4];

bool assign_op(int pos, int result)
{
	if(pos == 4)
	{
		return result == 23;
	}
	else
	{
		ops[pos] = '+';
		if(assign_op(pos+1, result+numbers[pos+1]))
			return true;
		ops[pos] = '-';
		if(assign_op(pos+1, result-numbers[pos+1]))
			return true;
		ops[pos] = '*';
		if(assign_op(pos+1, result*numbers[pos+1]))
			return true;
	}
	return false;
}

int main()
{
	bool possible;
	while(scanf("%d%d%d%d%d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4]))
	{
		if(numbers[0] == 0 && numbers[1] == 0 && numbers[2] == 0 && numbers[3] == 0 && numbers[4] == 0)
			break;
		std::sort(numbers, numbers+5);
		possible = false;
		do
		{
			if(assign_op(0, numbers[0]))
			{
				printf("Possible\n");
				possible = true;
				break;
			}
		} while(std::next_permutation(numbers, numbers+5));
		if(!possible)
			printf("Impossible\n");
	}
	return 0;
}
