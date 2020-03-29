#include <stdio.h>
#include <string.h>

#define MAX_MAXCAP 4500
#define MIN_MAXCAP 325

int wine, nsize;
int upper_bound;

struct bottle_t
{
	int min, max;
} bottle[100];

int dp[MAX_MAXCAP*99*99/100];	// 4500*99*0.99=441045

int solve()
{
	if(wine >= upper_bound)
		return 0;
	int i, j;
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	for(i = 0; i <= wine; i++)
	{
		if(dp[i] < 0)
			continue;
		for(j = 0; j < nsize; j++)
		{
			if(dp[i]+bottle[j].max-bottle[j].min > dp[i+bottle[j].min])
			{
				dp[i+bottle[j].min] = dp[i]+bottle[j].max-bottle[j].min;
			}
		}
	}
	int rmin = wine;
	for(i = wine; i > 0; i--)
	{
		if(dp[i] < 0)
			continue;
		if(wine-i-dp[i] <= 0)
			return 0;
		if(wine-i-dp[i] < rmin)
			rmin = wine-i-dp[i];
	}
	return rmin;
}

int main()
{
	int i, min_maxcap, tc;
	bool first_case = true;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &wine, &nsize);
		wine *= 1000;
		min_maxcap = MAX_MAXCAP;
		for(i = 0; i < nsize; i++)
		{
			scanf("%d%d", &bottle[i].min, &bottle[i].max);
			if(bottle[i].max < min_maxcap)
				min_maxcap = bottle[i].max;
		}
		if(!first_case)
			printf("\n");
		if(first_case)
			first_case = false;
		upper_bound = min_maxcap*99*99/100;
		if(min_maxcap%100)
			++upper_bound;
		printf("%d\n", solve());
	}
	return 0;
}
