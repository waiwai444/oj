#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>

#define MAXN 100

int n;
std::pair<int, int> pt[MAXN];

double dist(int x0, int y0, int x1, int y1)
{
	return sqrt((double)((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)));
}

double solve()
{
	int i, h = 0;
	double s = 0, d;
	std::sort(&pt[0], &pt[n]);
	for(i = n-2; i >= 0; i -= 2)
	{
		if(pt[i].second <= h)
			continue;
		d = dist(pt[i].first, pt[i].second, pt[i+1].first, pt[i+1].second);
		s += d*(pt[i].second-h)/(pt[i].second-pt[i+1].second);
		h = pt[i].second;
	}
	return s;
}

int main()
{
	int c, i, x, y;
	scanf("%d", &c);
	while(c--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			scanf("%d%d", &x, &y);
			pt[i] = std::make_pair(x, y);
		}
		printf("%.2f\n", solve());
	}
	return 0;
}

