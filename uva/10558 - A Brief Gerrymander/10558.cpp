#include <stdio.h>
#include <string.h>

int nn;
bool map[101][101];
int nstb, stb[101];
int navb;

#define FIRST_AV(i) (i)
#define LAST_AV(i) (100-navb+i)

bool valid_av[101];	// does this avenue have opposition-friendly neighborhoods
int count[101][101];	// for each north-south block, the number of opposition-friendly neighborhoods on each avenue
int sum[101][101];	// for each north-south block, the number of opposition-friendly neighborhoods on the north of each avenue
int target[101][101];	// the number of areas between two avenues that contain opposition-friendly neighborhoods

int dp[101][101];
int next[101][101];

void init()
{
	int i, j, k, cur_stb;
	memset(count, 0, sizeof(count));
	memset(sum, 0, sizeof(sum));
	memset(target, 0, sizeof(target));
	memset(dp, 0, sizeof(dp));
	for(i = 99; i >= 1; i--)
	{
		cur_stb = 1;
		for(j = 1; j < 100; j++)
		{
			if(j == stb[cur_stb+1])
				++cur_stb;
			if(map[i][j])
				++count[cur_stb][i];
		}
		for(j = 1; j <= nstb; j++)
			sum[j][i] = sum[j][i+1]+count[j][i];
	}
	for(i = 1; i < 100; i++)
	{
		for(j = i+1; j <= 100; j++)
		{
			for(k = 1; k <= nstb; k++)
			{
				if(sum[k][i]-sum[k][j] > 0)
					++target[i][j];
			}
			target[j][i] = target[i][j];
		}
	}
}

void solve()
{
	int i, j, k, b;
	init();
	// the second last boundary
	i = navb-1;
	for(j = LAST_AV(i); j >= FIRST_AV(i); j--)
	{
		dp[i][j] = target[j][100];
		next[i][j] = 100;
	}
	// from the third last to the second boundary
	for(i--; i > 1; i--)
	{
		for(j = LAST_AV(i); j >= FIRST_AV(i); j--)
		{
			if(!valid_av[j])
			{
				if(dp[i][j+1] > dp[i+1][j+1])
				{
					dp[i][j] = dp[i][j+1];
					next[i][j] = next[i][j+1];
				}
				else
				{
					dp[i][j] = dp[i+1][j+1];
					next[i][j] = j+1;
				}
			}
			else
			{
				for(k = j+1; k <= LAST_AV(i+1); k++)
				{
					if(dp[i+1][k]+target[j][k] > dp[i][j])
					{
						dp[i][j] = dp[i+1][k]+target[j][k];
						next[i][j] = k;
					}
				}
			}
		}
	}
	// the first boundary (the south boundary on avenue 1)
	for(k = FIRST_AV(2); k <= LAST_AV(2); k++)
	{
		if(dp[2][k]+target[1][k] > dp[1][1])
		{
			dp[1][1] = dp[2][k]+target[1][k];
			next[1][1] = k;
		}
	}
}

void output()
{
	int i, c = 1;
	printf("%d 1", navb);
	for(i = 2; i < navb; i++)
	{
		c = next[i-1][c];
		printf(" %d", c);
	}
	printf(" 100\n");
}

int main()
{
	int i, st, av;
	while(scanf("%d", &nn), nn >= 0)
	{
		memset(map, false, sizeof(map));
		memset(valid_av, false, sizeof(valid_av));
		for(i = 0; i < nn; i++)
		{
			scanf("%d%d", &st, &av);
			map[av][st] = true;
			if(!valid_av[av])
				valid_av[av] = true;
		}
		scanf("%d", &nstb);
		for(i = 1; i <= nstb; i++)
			scanf("%d", &stb[i]);
		scanf("%d", &navb);
		solve();
		output();
	}
	return 0;
}
