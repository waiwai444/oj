#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

int mm, kk;
int pr[6][6];	// product
int ht[6][6];	// heat
int dp[10][10][10][10][10][10];

int solve(int nc[], int k)
{
	int i, j, t;
	int *h = &dp[nc[0]][nc[1]][nc[2]][nc[3]][nc[4]][nc[5]];
	if(k <= 1)
		return 0;
	if(*h < INF)
		return *h;
	for(i = 0; i < mm; i++)
	{
		if(nc[i] > 0)
		{
			--nc[i];
			for(j = 0; j < mm; j++)
			{
				if(nc[j] > 0)
				{
					--nc[j];
					++nc[pr[i][j]];
					t = ht[i][j]+solve(nc, k-1);
					if(t < *h)
						*h = t;
					++nc[j];
					--nc[pr[i][j]];
				}
			}
			++nc[i];
		}
	}
	return *h;
}

int main()
{
	int i, j, t, tc;
	int nc[6];
	char ch[2];
	scanf("%d", &tc);
	while(tc--)
	{
		memset(nc, 0, sizeof(nc));
		scanf("%d", &mm);
		for(i = 0; i < mm; i++)
		{
			for(j = 0; j < mm; j++)
			{
				scanf("%d%d\n", &t, &ht[i][j]);
				pr[i][j] = t-1;
			}
		}
		scanf("%d", &kk);
		for(i = 0; i < kk; i++)
		{
			scanf("%d", &t);
			++nc[t-1];
		}
		scanf("%s", ch);
		memset(dp, 0x3f, sizeof(dp));
		printf("%d\n", solve(nc, kk));
	}
	return 0;
}
