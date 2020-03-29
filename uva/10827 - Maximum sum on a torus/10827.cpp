#include <stdio.h>

int n;
int torus[150][150];
int col_sum[150][150];

int solve()
{
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			torus[i+n][j] = torus[i][j+n] = torus[i+n][j+n] = torus[i][j];
	
	int m = 2*n-1;
	for(j = 0; j < m; j++)
	{
		col_sum[0][j] = torus[0][j];
		for(i = 1; i < m; i++)
			col_sum[i][j] = col_sum[i-1][j]+torus[i][j];
	}
	
	int result = -100, sum, l, r, k, tmp;
	for(i = 0; i < n; i++)
		for(j = i; j < i+n; j++)
		{
			if(i > 0 && j == i+n-1)
				break;
			sum = 0;
			for(l = r = 0; r < m; r++)
			{
				sum += col_sum[j][r]-(i > 0 ? col_sum[i-1][r] : 0);
				if(sum > result)
					result = sum;
				if(sum < 0)
				{
					sum = 0;
					l = r+1;
				}				
				else if(r-l+1 == n)
				{
					tmp = (sum -= col_sum[j][l]-(i > 0 ? col_sum[i-1][l] : 0));
					for(k = ++l; k <= r; k++)
					{
						tmp -= col_sum[j][k]-(i > 0 ? col_sum[i-1][k] : 0);
						if(tmp >= sum)
						{
							sum = tmp;
							l = k+1;
						}
					}
				}
				if(l >= n)
					break;
			}
		}
	
	return result;
}

int main()
{
	int i, j, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &torus[i][j]);
		printf("%d\n", solve());
	}
	return 0;
}
