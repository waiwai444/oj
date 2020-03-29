#include <stdio.h>
#include <string.h>
#include <algorithm>

struct bigint_t
{
	char d[1002];
	int msd;
} in, res;

bool operator>(const bigint_t &x, const bigint_t &y)
{
	if(x.msd > y.msd)
		return true;
	if(x.msd < y.msd)
		return false;
	for(int i = x.msd; i >= 0; i--)
	{
		if(x.d[i] > y.d[i])
			return true;
		else if(x.d[i] < y.d[i])
			return false;
	}
	return false;
}

void multiply(const bigint_t &x, char y, bigint_t *z)
{
	int i;
	char t, c = 0;
	for(i = 0; i <= x.msd; i++)
	{
		t = x.d[i]*y+c;
		z->d[i] = t%10;
		c = t/10;
	}
	if(c > 0)
		z->d[i++] = c;
	z->msd = y != 0 ? i-1 : 0;
}

void subtract(const bigint_t &x, const bigint_t &y, bigint_t *z) // x >= y
{
	char t, c = 0, d;
	int i, msd = x.msd;
	z->msd = 0;
	for(i = 0; i <= msd; i++)
	{
		t = x.d[i]-c;
		d = i > y.msd ? 0 : y.d[i];
		if(t < d)
		{
			t += 10;
			c = 1;
		}
		else
			c = 0;
		z->d[i] = t-d;
		if(z->d[i])
			z->msd = i;
	}
}

void lshift(bigint_t *x, int s)
{
	for(int i = x->msd; i >= 0; i--)
		x->d[i+s] = x->d[i];
	if(x->msd > 0 || x->d[0] != 0)
		x->msd += s;
}

void solve()
{
	int i, j, h, l;
	static bigint_t dvd, dvs, tmp[10];
	in.msd = strlen(in.d)-1;
	std::reverse(in.d, &in.d[in.msd+1]);
	for(i = 0; i <= in.msd; i++)
		in.d[i] -= '0';
	res.msd = in.msd/2;
	if(in.msd&1)
	{
		dvd.msd = 1;
		dvd.d[1] = in.d[in.msd];
		dvd.d[0] = in.d[in.msd-1];
	}
	else
	{
		dvd.msd = 0;
		dvd.d[0] = in.d[in.msd];
	}
	dvs.msd = 0;
	for(i = res.msd; i >= 0; i--)
	{
		h = 9;
		l = 0;
		while(l <= h)
		{
			j = (h+l)/2;
			dvs.d[0] = j;
			multiply(dvs, j, &tmp[j]);
			if(tmp[j] > dvd)
				h = j-1;
			else
				l = j+1;
		}
		res.d[i] = l-1;
		if(i > 0)
		{
			subtract(dvd, tmp[l-1], &dvd);
			lshift(&dvd, 2);
			dvd.d[1] = in.d[2*i-1];
			dvd.d[0] = in.d[2*i-2];
			if(dvd.msd == 0)
				dvd.msd = dvd.d[1] != 0 ? 1 : 0;
			for(j = i; j <= res.msd; j++)
				dvs.d[j-i+1] = res.d[j];
			dvs.d[0] = 0;
			dvs.msd = j-i;
			multiply(dvs, 2, &dvs);
		}
	}
	std::reverse(res.d, &res.d[res.msd+1]);
	for(i = 0; i <= res.msd; i++)
		res.d[i] += '0';
	res.d[res.msd+1] = '\0';
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s", in.d);
		solve();
		printf("%s\n", res.d);
		if(tc)
			printf("\n");
	}
	return 0;
}
