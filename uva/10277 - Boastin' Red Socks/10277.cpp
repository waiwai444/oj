#include <stdio.h>
#include <math.h>

unsigned long p, q;
int r, b;

void solve()
{
	int i, sr;
	long long t;
	r = b = 0;
	if(p == 0)
	{
		b = 2;
		return;
	}
	for(i = 2; i <= 50000; i++)
	{
		t = (long long)i*(i-1)*p;
		if(t%q == 0)
		{
			t /= q;
			sr = (sqrt(double(1+4*t))+0.5);
			if((long long)sr*sr == 1+4*t)
			{
				r = (1+sr)/2;
				b = i-r;
				break;
			}
		}
	}
}

int main()
{
	while(scanf("%lu%lu", &p, &q), q)
	{
		solve();
		if(r+b == 0)
			printf("impossible\n");
		else
			printf("%d %d\n", r, b);
	}
	return 0;
}

