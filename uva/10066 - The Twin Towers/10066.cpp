#include <stdio.h>

int n1, n2;
int arr1[100], arr2[100];
int dp[100][100];

int main()
{
	int i, j, tc = 0;;
	while(scanf("%d%d", &n1, &n2), n1)
	{
		for(i = 0; i < n1; i++)
			scanf("%d", &arr1[i]);
		for(i = 0; i < n2; i++)
			scanf("%d", &arr2[i]);
		dp[0][0] = arr1[0] == arr2[0] ? 1 : 0;
		for(i = 1; i < n1; i++)
			dp[i][0] = dp[i-1][0] == 1 || arr1[i] == arr2[0] ? 1 : 0;
		for(j = 1; j < n2; j++)
			dp[0][j] = dp[0][j-1] == 1 || arr1[0] == arr2[j] ? 1 : 0;
		for(i = 1; i < n1; i++)
		{
			for(j = 1; j < n2; j++)
			{
				dp[i][j] = 0;
				if(arr1[i] == arr2[j])
					dp[i][j] = dp[i-1][j-1]+1;
				if(dp[i-1][j] > dp[i][j])
					dp[i][j] = dp[i-1][j];
				if(dp[i][j-1] > dp[i][j])
					dp[i][j] = dp[i][j-1];
			}
		}
		printf("Twin Towers #%d\nNumber of Tiles : %d\n\n", ++tc, dp[n1-1][n2-1]);
	}
	return 0;
}