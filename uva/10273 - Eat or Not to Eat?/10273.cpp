#include <cstdio>

int n;
struct cow_t
{
	int t, m[10];
} cows[1001];
int next[1001];

int cow, day;

int gcd(int x, int y)
{
	return y == 0 ? x : gcd(y, x%y);
}

inline int lcm(int x, int y)
{
	return x*y/gcd(x, y);
}

void solve()
{
	int i, j, k, t = 1, c = 0, min, p, q, d = 0;
	day = 0;
	for(i = 1; i <= n; i++)
		t = lcm(t, cows[i].t);
	for(i = 0; ; i++)
	{
		min = 1000, p = q = -1;
		for(k = 0, j = next[0]; j != -1; k = j, j = next[j])
		{
			int m = cows[j].m[i%cows[j].t];
			if(m < min)
			{
				min = m;
				p = j;
				q = k;
			}
			else if(m == min)
				p = q = -1;
		}
		if(p > 0)
		{
			next[q] = next[p];
			++d;
			day = i+1;
			c = 0;
		}
		else if(++c >= t)
			break;
	}
	cow = n-d;
}

int main()
{
	int i, j, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		next[0] = 1;
		for(i = 1; i <= n; i++)
		{
			scanf("%d", &cows[i].t);
			for(j = 0; j < cows[i].t; j++)
				scanf("%d", &cows[i].m[j]);
			next[i] = i+1;
		}
		next[n] = -1;
		solve();
		printf("%d %d\n", cow, day);
	}
	return 0;
}

