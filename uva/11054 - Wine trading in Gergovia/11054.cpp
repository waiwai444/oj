#include <stdio.h>

int n;
int demand[100000];
int buyer[100000], seller[100000], nb, ns;

void solve()
{
	long long total = 0;
	int i, j, b, s;
	i = j = 0;
	while(i < nb)
	{
		b = buyer[i];
		s = seller[j];
		if(b < s)
		{
			while(demand[b] > 0 && demand[b] >= -demand[s])
			{
				demand[b] += demand[s];
				total += -demand[s]*(s-b);
				demand[s] = 0;
				s = seller[++j];
			}
			if(demand[b] > 0)
			{
				demand[s] += demand[b];
				total += demand[b]*(s-b);
				demand[b] = 0;
			}
			++i;
		}
		else
		{
			while(demand[s] < 0 && -demand[s] >= demand[b])
			{
				demand[s] += demand[b];
				total += demand[b]*(b-s);
				demand[b] = 0;
				b = buyer[++i];
			}
			if(demand[s] < 0)
			{
				demand[b] += demand[s];
				total += -demand[s]*(b-s);
				demand[s] = 0;
			}
			++j;
		}
	}
	printf("%lld\n", total);
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		nb = ns = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%d", &demand[i]);
			if(demand[i] > 0)
				buyer[nb++] = i;
			else if(demand[i] < 0)
				seller[ns++] = i;
		}
		solve();
	}
	return 0;
}
