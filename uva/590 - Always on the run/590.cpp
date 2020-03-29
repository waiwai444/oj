#include <stdio.h>

int n, k;

struct FlightInfo
{
	int d;
	int cost[30];
} conn[10][10];

int dp[1000][10];

int main()
{
	int i, j, c, t, tc = 0;
	while(scanf("%d%d", &n, &k), n)
	{
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(i != j)
				{
					scanf("%d", &conn[i][j].d);
					for(c = 0; c < conn[i][j].d; c++)
						scanf("%d", &conn[i][j].cost[c]);
				}
		for(i = 1; i < n; i++)
		{
			if(conn[0][i].cost[0] > 0)
				dp[0][i] = conn[0][i].cost[0];
			else
				dp[0][i] = 0;
		}
		for(i = 1; i < k; i++)
		{
			for(j = 0; j < n; j++)
			{
				dp[i][j] = 0;
				for(c = 0; c < n; c++)
				{
					if(c == j || dp[i-1][c] == 0)
						continue;
					t = conn[c][j].cost[i%conn[c][j].d];
					if(t == 0)
						continue;
					if(dp[i][j] == 0 || dp[i-1][c]+t < dp[i][j])
						dp[i][j] = dp[i-1][c]+t;
				}
			}
		}
		printf("Scenario #%d\n", ++tc);
		if(dp[k-1][n-1] == 0)
			printf("No flight possible.\n\n");
		else
			printf("The best flight costs %d.\n\n", dp[k-1][n-1]);
	}
	return 0;
}
