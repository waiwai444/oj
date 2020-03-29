#include <stdio.h>

int n;
int seq[10000];
int mlen[10000], mlen_r[10000];
int last[10001], ml;

int bisect(int i)
{
	int low, high, mid;
	low = 1;
	high = ml;
	while(low <= high)
	{
		mid = (low+high)/2;
		if(seq[i] > seq[last[mid]])
			low = mid+1;
		else if(seq[i] < seq[last[mid]])
			high = mid-1;
		else
			return mid;
	}
	return low;
}

void lis()
{
	int p;
	mlen[0] = 1;
	last[1] = 0;
	ml = 1;
	for(int i = 1; i < n; i++)
	{
		p = bisect(i);
		last[p] = i;
		mlen[i] = p;
		if(p > ml)
			ml = p;
	}
}

void lis_r()
{
	int p;
	mlen_r[n-1] = 1;
	last[1] = n-1;
	ml = 1;
	for(int i = n-1; i >= 0; i--)
	{
		p = bisect(i);
		last[p] = i;
		mlen_r[i] = p;
		if(p > ml)
			ml = p;
	}
}

inline int min(int x, int y)
{
	return x <= y ? x : y;
}

int main()
{
	int i, m, t;
	while(scanf("%d", &n) != EOF)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &seq[i]);
		lis();
		lis_r();
		m = 1;
		for(i = 0; i < n; i++)
		{
			t = min(mlen[i], mlen_r[i]);
			if(2*t-1 > m)
				m = 2*t-1;
		}
		printf("%d\n", m);
	}
	return 0;
}