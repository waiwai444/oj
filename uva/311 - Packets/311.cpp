#include <stdio.h>

int sq_num[6];

void solve()
{
	int result = sq_num[5]+sq_num[4]+sq_num[3];
	
	if(sq_num[0] > 0)
		sq_num[0] -= 11*sq_num[4];
	
	if(sq_num[1] > 0)
	{
		sq_num[1] -= 5*sq_num[3];
		if(sq_num[1] < 0 && sq_num[0] > 0)
			sq_num[0] -= 4*(-sq_num[1]);
	}
	
	result += sq_num[2]/4;
	int r = sq_num[2]%4;
	if(r != 0)
	{
		result++;
		if(r == 1)
		{
			if(sq_num[1] >= 5)
			{
				sq_num[1] -= 5;
				sq_num[0] -= 7;
			}
			else
			{
				if(sq_num[1] == 4)
					sq_num[0] -= 11;
				else if(sq_num[1] == 3)
					sq_num[0] -= 15;
				else if(sq_num[1] == 2)
					sq_num[0] -= 19;
				else if(sq_num[1] == 1)
					sq_num[0] -= 23;
				else
					sq_num[0] -= 27;
				sq_num[1] = 0;
			}
		}
		else if(r == 2)
		{
			if(sq_num[1] >= 3)
			{
				sq_num[1] -= 3;
				sq_num[0] -= 6;
			}
			else
			{
				if(sq_num[1] == 2)
					sq_num[0] -= 10;
				else if(sq_num[1] == 1)
					sq_num[0] -= 14;
				else
					sq_num[0] -= 18;
				sq_num[1] = 0;
			}
		}
		else if(r == 3)
		{
			if(sq_num[1] >= 1)
			{
				sq_num[1]--;
				sq_num[0] -= 5;
			}
			else
				sq_num[0] -= 9;
		}
	}
	
	if(sq_num[1] > 0)
	{
		result += sq_num[1]/9;
		r = sq_num[1]%9;
		if(r != 0)
		{
			result++;
			sq_num[0] -= (36-r*4);
		}
	}
	
	if(sq_num[0] > 0)
	{
		result += sq_num[0]/36;
		r = sq_num[0]%36;
		if(r != 0)
			result++;
	}
	
	printf("%d\n", result);
}

int main()
{
	while(scanf("%d%d%d%d%d%d", &sq_num[0], &sq_num[1], &sq_num[2], &sq_num[3], &sq_num[4], &sq_num[5]))
	{
		if(sq_num[0] == 0 && sq_num[1] == 0 && sq_num[2] == 0 && sq_num[3] == 0 && sq_num[4] == 0 && sq_num[5] == 0)
			break;
		solve();
	}
	return 0;
}
