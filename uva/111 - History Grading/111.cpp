#include <stdio.h>

int n;
int rank[20], stu_ord[20];
int dp[21];

int main()
{
	int i, first, last, mid, ans, max;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &rank[i]);
	while(scanf("%d", &ans) != EOF)
	{
		stu_ord[ans-1] = rank[0];
		for(i = 1; i < n; i++)
		{
			scanf("%d", &ans);
			stu_ord[ans-1] = rank[i];
		}
		
		dp[1] = stu_ord[0];
		max = 1;
		for(i = 1; i < n; i++)
		{
			first = 1;
			last = max;
			while(first <= last)
			{
				mid = (first+last)/2;
				if(dp[mid] < stu_ord[i])
					first = mid+1;
				else
					last = mid-1;
			}
			dp[first] = stu_ord[i];
			if(first > max)
				max = first;
		}
		
		printf("%d\n", max);
	}
	return 0;
}
