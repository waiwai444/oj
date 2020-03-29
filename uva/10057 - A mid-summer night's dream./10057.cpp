#include <stdio.h>
#include <string.h>

int n, nu;
int cnt[65536], unique_set[65536], pre_cnt[65536];

int main()
{
	int i, t, min, max, min_A, nA, ndA;
	while(scanf("%d", &n) != EOF)
	{
		memset(cnt, 0, sizeof(cnt));
		min = 65536;
		max = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%d", &t);
			cnt[t]++;
			if(t > max)
				max = t;
			if(t < min)
				min = t;
		}
		
		for(nu = 0, i = min; i <= max; i++)
		{
			if(cnt[i] > 0)
			{
				unique_set[nu] = i;
				pre_cnt[nu] = cnt[i]+(nu == 0 ? 0 : pre_cnt[nu-1]);
				nu++;
			}
		}
		
		i = 0;
		while(pre_cnt[i] < n-pre_cnt[i]) i++;
		min_A = unique_set[i];
		nA = cnt[min_A];
		while(pre_cnt[i] == n-pre_cnt[i])
		{
			i++;
			nA += cnt[unique_set[i]];
		}
		ndA = unique_set[i]-min_A+1;
		printf("%d %d %d\n", min_A, nA, ndA);
	}
	return 0;
}
