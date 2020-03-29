#include <stdio.h>

#define MAX 1000001
#define MM 1000

int n;
int cnt1[MAX], cnt2[MAX];
int minc[MAX];

int gcd(int x, int y)
{
	return y ? gcd(y, x%y) : x;
}

void solve()
{
	int i, j, a, b, c, a2, b2, c2;
	for(i = 0; i < MAX; i++)
		minc[i] = MAX;
	for(i = 2; i < MM; i++)
	{
		for(j = 1; j < i; j++)
		{
			if(gcd(i, j) > 1 || !(i&1^j&1))
				continue;
			a2 = a = i*i-j*j;
			b2 = b = 2*i*j;
			c2 = c = i*i+j*j;
			if(c >= MAX)
				break;
			++cnt1[c];
			while(c2 < MAX)
			{
				if(minc[a2] > c2)
					minc[a2] = c2;
				if(minc[b2] > c2)
					minc[b2] = c2;
				minc[c2] = c2;
				a2 += a;
				b2 += b;
				c2 += c;
			}
		}
	}
	for(i = 1; i < MAX; i++)
	{
		cnt1[i] += cnt1[i-1];
		++cnt2[minc[i]];
		cnt2[i] += cnt2[i-1];
	}
}

int main()
{
	solve();
	while(scanf("%d", &n) != EOF)
	{
		printf("%d %d\n", cnt1[n], n-cnt2[n]);
	}
	return 0;
}
