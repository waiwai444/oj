#include <stdio.h>
#include <string.h>

struct dp_struct
{
	bool visited;
	unsigned char result;
	unsigned char basket_used;
	int basket_flag;
};

int n;
int piles[4][40];
dp_struct dp[41][41][41][41];

int solve(int p[])
{
	int i, cur, tmp;
	dp_struct *cdp = &dp[p[0]][p[1]][p[2]][p[3]];
	dp_struct *ndp;
	if(cdp->visited)
		return cdp->result;
	cdp->visited = true;
	for(i = 0; i < 4; i++)
	{
		if(p[i] > 0)
		{
			cur = piles[i][p[i]-1];
			--p[i];
			ndp = &dp[p[0]][p[1]][p[2]][p[3]];
			if(cdp->basket_flag & (1<<cur))
			{
				tmp = 1;
				ndp->basket_used = cdp->basket_used-1;
			}
			else
			{
				tmp = 0;
				ndp->basket_used = cdp->basket_used+1;
			}
			ndp->basket_flag = cdp->basket_flag^(1<<cur);
			if(ndp->basket_used < 5)
				tmp += solve(p);
			++p[i];
			if(cdp->result < tmp)
				cdp->result = tmp;
		}
	}
	return cdp->result;
}

int main()
{
	int i, j, p[4];
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			for(j = 0; j < 4; j++)
				scanf("%d", &piles[j][n-i-1]);
		memset(dp, 0, sizeof(dp));
		p[0] = p[1] = p[2] = p[3] = n;
		printf("%d\n", solve(p));
	}
	return 0;
}
