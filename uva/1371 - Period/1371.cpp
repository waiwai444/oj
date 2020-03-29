#include <stdio.h>
#include <string.h>
#include <algorithm>

char strx[5001];
char stry[51];
int lenx, leny;

int dp[5000][50];

bool match(int lim)
{
	int i, j, tmp;
	int inf = lim+1; // means impossible
	bool flag;

	dp[0][0] = strx[0] == stry[0] ? 0 : 1;
	if(dp[0][0] > lim)
		return false;
	for(i = 1; i < leny; i++)
	{
		dp[0][i] = std::min(inf, strx[0] == stry[i] ? i : dp[0][i-1]+1);
	}

	for(i = 1; i < lenx; i++)
	{
		flag = false;
		dp[i][0] = std::min(inf, i+(strx[i] == stry[0] ? 0 : 1));
		if(dp[i-1][leny-1] < inf)
			dp[i][0] = std::min(dp[i][0], strx[i] == stry[0] ? 0 : 1);
		if(dp[i][0] < inf)
			flag = true;

		for(j = 1; j < leny; j++)
		{
			dp[i][j] = std::min(inf, dp[i-1][j-1]+(strx[i] == stry[j] ? 0 : 1));
			dp[i][j] = std::min(dp[i][j], dp[i][j-1]+1);
			dp[i][j] = std::min(dp[i][j], dp[i-1][j]+1);
			if(dp[i][j] < inf && !flag)
				flag = true;
		}

		if(!flag)
			return false;
	}

	return dp[lenx-1][leny-1] < inf;
}

int solve()
{
	int i, m, l = 0, h = leny;
	while(l <= h)
	{
		m = (l+h)/2;
		if(match(m))
			h = m-1;
		else
			l = m+1;
	}
	return h+1;
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s%s", stry, strx);
		lenx = strlen(strx);
		leny = strlen(stry);
		printf("%d\n", solve());
	}
	return 0;
}
