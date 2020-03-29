#include <stdio.h>
#include <string.h>

int n, h, f[25], d[25], t[24];
int res[25], tot;

void solve()
{
	int i, j, k, l, max;
	int tmp_f[25];
	int cur_res[25], cur_tot;
	int tm = 0, ta;
	memset(res, 0, sizeof(res));
	tot = -1;
	for(i = 0; i < n; i++)
	{
		memcpy(tmp_f, f, sizeof(tmp_f));
		memset(cur_res, 0, sizeof(cur_res));
		cur_tot = 0;
		ta = h-tm;
		for(j = 0; j < ta; j++)
		{
			max = tmp_f[0];
			l = 0;
			for(k = 1; k <= i; k++)
			{
				if(tmp_f[k] > max)
				{
					l = k;
					max = tmp_f[k];
				}
			}
			cur_res[l]++;
			tmp_f[l] -= d[l];
			if(tmp_f[l] < 0)
				tmp_f[l] = 0;
			cur_tot += max;
		}
		if(cur_tot > tot)
		{
			tot = cur_tot;
			memcpy(res, cur_res, sizeof(res));
		}
		tm += t[i];
	}
}

int main()
{
	int i;
	bool first = true;
	while(scanf("%d", &n), n)
	{
		scanf("%d", &h);
		h *= 12;
		for(i = 0; i < n; i++) scanf("%d", &f[i]);
		for(i = 0; i < n; i++) scanf("%d", &d[i]);
		for(i = 0; i < n-1; i++) scanf("%d", &t[i]);
		
		solve();
		
		if(first) first = false;
		else printf("\n");
		printf("%d", res[0]*5);
		for(i = 1; i < n; i++) printf(", %d", res[i]*5);
		printf("\nNumber of fish expected: %d\n", tot);
	}
	return 0;
}
