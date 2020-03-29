#include <stdio.h>
#include <string.h>

int maxn, len1, len2;
int seq1[62500], seq2[62500];
int ord[62501];
int lis_len, dp[62501];

int binary_search(int cur)
{
	int low = 1, high = lis_len, mid, tmp;
	while(low <= high)
	{
		mid = (low+high)/2;
		tmp = ord[seq1[dp[mid]]];
		if(tmp < cur)
			low = mid+1;
		else if(tmp > cur)
			high = mid-1;
		else
			return mid;
	}
	return low;
}

void solve()
{
	int i, p;
	memset(ord, -1, sizeof(ord));
	for(i = 0; i < len2; i++)
		ord[seq2[i]] = i;
	dp[1] = 0;
	lis_len = 1;
	for(i = 1; i < len1; i++)
	{
		if(ord[seq1[i]] >= 0)
		{
			p = binary_search(ord[seq1[i]]);
			if(p > lis_len)
			{
				dp[lis_len = p] = i;
			}
			else if(seq1[dp[p]] != seq1[i])
			{
				dp[p] = i;
			}
		}
	}
}

int main()
{
	int i, c, tc, n, p, q;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%d%d%d", &n, &p, &q);
		maxn = n*n;
		len1 = p+1;
		len2 = q+1;
		for(i = 0; i < len1; i++)
			scanf("%d", &seq1[i]);
		for(i = 0; i < len2; i++)
			scanf("%d", &seq2[i]);
		solve();
		printf("Case %d: %d\n", c, lis_len);
	}
	return 0;
}
