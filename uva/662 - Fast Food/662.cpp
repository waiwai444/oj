#include <stdio.h>

int nrest, ndepo;
int pos[200];
int dp[30][200], prev[30][200];
int diff[200][200], sep[200][200];

void init()
{
	int i, j, k;
	for(i = 0; i < nrest-1; i++)
	{
		sep[i][i+1] = i;
		for(j = i+2; j < nrest; j++)
		{
			for(k = sep[i][j-1]+1; k < j; k++)
			{
				if(pos[k]-pos[i] > pos[j]-pos[k]) break;
			}
			sep[i][j] = k-1;
		}
	}
	for(i = 0; i < nrest-1; i++)
	{
		for(j = i+1; j < nrest; j++)
		{
			diff[i][j] = (pos[j]-pos[i])*(nrest-j);
			for(k = sep[i][j]+1; k < j; k++)
			{
				diff[i][j] += (pos[k]-pos[i])-(pos[j]-pos[k]);
			}
		}
	}
}

void solve()
{
	int i, j, k, l;
	init();
	dp[0][0] = 0;
	for(i = 1; i < nrest; i++)
		dp[0][0] += pos[i]-pos[0];
	for(i = 1; i < nrest; i++)
		dp[0][i] = dp[0][i-1]+(pos[i]-pos[i-1])*(i+i-nrest);
	for(i = 1; i < ndepo; i++)
	{
		for(j = i; j < nrest; j++)
		{
			dp[i][j] = 0x3f3f3f3f;
			for(k = i-1; k < j; k++)
			{
				int tmp = dp[i-1][k]-diff[k][j];
				if(tmp < dp[i][j])
				{
					dp[i][j] = tmp;
					prev[i][j] = k;
				}
			}
		}
	}
}

void output()
{
	int i, min = dp[ndepo-1][ndepo-1];
	int depo_pos[30], right[30], left;
	depo_pos[ndepo-1] = ndepo-1;
	for(i = ndepo; i < nrest; i++)
	{
		if(min > dp[ndepo-1][i])
		{
			min = dp[ndepo-1][i];
			depo_pos[ndepo-1] = i;
		}
	}
	right[ndepo-1] = nrest-1;
	for(i = ndepo-2; i >= 0; i--)
	{
		depo_pos[i] = prev[i+1][depo_pos[i+1]];
		right[i] = sep[depo_pos[i]][depo_pos[i+1]];
	}
	for(i = left = 0; i < ndepo; i++)
	{
		if(right[i] == left)
			printf("Depot %d at restaurant %d serves restaurant %d\n", i+1, left+1, left+1);
		else
			printf("Depot %d at restaurant %d serves restaurants %d to %d\n", i+1, depo_pos[i]+1, left+1, right[i]+1);
		left = right[i]+1;
	}	
	printf("Total distance sum = %d\n\n", min);
}

int main()
{
	int i, tc = 0;
	while(scanf("%d%d", &nrest, &ndepo), nrest)
	{
		for(i = 0; i < nrest; i++)
			scanf("%d", &pos[i]);
		solve();
		printf("Chain %d\n", ++tc);
		output();
	}
	return 0;
}
