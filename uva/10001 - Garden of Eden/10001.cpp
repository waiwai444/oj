
#include <stdio.h>

int id;
int cells;	// 4 <= cells <= 32
char state[33];
char prevState[33];

int ancestorNum[2];	// number of ancestors to cause transferring to 0 or 1
char ancestor[2][8][3];	// ancestors to cause transferring to 0 or 1

void getAutomaton(int id)
{
	ancestorNum[0] = ancestorNum[1] = 0;
	int bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][0] = ancestor[bit][ancestorNum[bit]][1] = ancestor[bit][ancestorNum[bit]][2] = 0;
	ancestorNum[bit]++;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][0] = ancestor[bit][ancestorNum[bit]][1] = 0;
	ancestor[bit][ancestorNum[bit]++][2] = 1;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][0] = ancestor[bit][ancestorNum[bit]][2] = 0;
	ancestor[bit][ancestorNum[bit]++][1] = 1;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][1] = ancestor[bit][ancestorNum[bit]][2] = 1;
	ancestor[bit][ancestorNum[bit]++][0] = 0;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][1] = ancestor[bit][ancestorNum[bit]][2] = 0;
	ancestor[bit][ancestorNum[bit]++][0] = 1;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][0] = ancestor[bit][ancestorNum[bit]][2] = 1;
	ancestor[bit][ancestorNum[bit]++][1] = 0;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][0] = ancestor[bit][ancestorNum[bit]][1] = 1;
	ancestor[bit][ancestorNum[bit]++][2] = 0;
	bit = id & 1;
	id >>= 1;
	ancestor[bit][ancestorNum[bit]][0] = ancestor[bit][ancestorNum[bit]][1] = ancestor[bit][ancestorNum[bit]][2] = 1;
	ancestorNum[bit]++;
}

bool backtrack(int curPos)
{
	if(curPos == 0)
	{
		for(int i = 0; i < ancestorNum[state[0]]; i++)
		{
			prevState[cells - 1] = ancestor[state[0]][i][0];
			prevState[0] = ancestor[state[0]][i][1];
			prevState[1] = ancestor[state[0]][i][2];
			if(backtrack(1))
				return true;
		}
	}
	else if(curPos == cells - 2)
	{
		for(int i = 0; i < ancestorNum[state[curPos]]; i++)
		{
			if(prevState[curPos - 1] != ancestor[state[curPos]][i][0] || prevState[curPos] != ancestor[state[curPos]][i][1] || prevState[curPos + 1] != ancestor[state[curPos]][i][2])
				continue;
			if(backtrack(curPos + 1))
				return true;
		}
	}
	else if(curPos == cells - 1)
	{
		for(int i = 0; i < ancestorNum[state[curPos]]; i++)
		{
			if(prevState[curPos - 1] != ancestor[state[curPos]][i][0] || prevState[curPos] != ancestor[state[curPos]][i][1] || prevState[0] != ancestor[state[curPos]][i][2])
				continue;
			return true;
		}
	}
	else
	{
		for(int i = 0; i < ancestorNum[state[curPos]]; i++)
		{
			if(prevState[curPos - 1] != ancestor[state[curPos]][i][0] || prevState[curPos] != ancestor[state[curPos]][i][1])
				continue;
			prevState[curPos + 1] = ancestor[state[curPos]][i][2];
			if(backtrack(curPos + 1))
				return true;
		}
	}
	return false;
}

int main(int argc, char** argv)
{
	while(EOF != scanf("%d %d %s", &id, &cells, state))
	{
		for(int i = 0; i < cells; i++)
			state[i] -= '0';
		getAutomaton(id);
		if(backtrack(0))
			printf("REACHABLE\n");
		else
			printf("GARDEN OF EDEN\n");
	}
	return 0;
}
