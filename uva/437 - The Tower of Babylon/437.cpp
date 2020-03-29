#include <stdio.h>
#include <algorithm>

int n;
struct Cubic
{
	int x, y, z;
} blk[90];
int dp[90];

bool cmp(const Cubic &c1, const Cubic &c2)
{
	return c1.x*c1.y < c2.x*c2.y;
}

int solve()
{
	int i, j, max;
	max = dp[0] = blk[0].z;
	for(i = 1; i < n; i++)
	{
		dp[i] = blk[i].z;
		for(j = 0; j < i; j++)
		{
			if((blk[i].x > blk[j].x && blk[i].y > blk[j].y) || (blk[i].x > blk[j].y && blk[i].y > blk[j].x))
			{
				if(dp[j]+blk[i].z > dp[i])
					dp[i] = dp[j]+blk[i].z;
			}
		}
		if(dp[i] > max)
			max = dp[i];
	}
	return max;
}

int main()
{
	int i, tc = 0;
	while(scanf("%d", &n), n)
	{
		n *= 3;
		for(i = 0; i < n; i += 3)
		{
			scanf("%d%d%d", &blk[i].x, &blk[i].y, &blk[i].z);
			blk[i+1].x = blk[i].x; blk[i+1].y = blk[i].z; blk[i+1].z = blk[i].y;
			blk[i+2].x = blk[i].z; blk[i+2].y = blk[i].y; blk[i+2].z = blk[i].x;
		}
		std::sort(blk, blk+n, cmp);
		printf("Case %d: maximum height = %d\n", ++tc, solve());
	}
	return 0;
}