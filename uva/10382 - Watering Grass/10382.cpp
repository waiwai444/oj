#include <stdio.h>
#include <math.h>
#include <algorithm>

struct Cross
{
	double left, right;
};

int num, length, width;
Cross cross[10000];

bool cmp(const Cross &c1, const Cross &c2)
{
	return c1.left < c2.left;
}

void solve()
{
	std::sort(cross, cross+num, cmp);
	
	double cur = 0, max;
	int i, result = 0;
	
	i = 0;
	while(i < num)
	{
		max = 0;
		while(i < num && cross[i].left <= cur)
		{
			if(cross[i].right > max)
				max = cross[i].right;
			i++;
		}
		if(max <= cur)
			break;
		cur = max;
		result++;
		if(cur >= length)
			break;
	}
	
	if(cur >= length)
		printf("%d\n", result);
	else
		printf("-1\n");
}

int main()
{
	int n, pos, rad;
	double d;
	while(scanf("%d%d%d", &n, &length, &width) != EOF)
	{
		num = 0;
		while(n--)
		{
			scanf("%d%d", &pos, &rad);
			if(pos+rad <= 0 || pos-rad >= length || rad*2 <= width)
				continue;
			d = sqrt((double)rad*rad-(double)width*width/4.0);
			if(pos+d <= 0 || pos-d >= length)
				continue;
			cross[num].left = pos-d;
			cross[num].right = pos+d;
			num++;
		}
		solve();
	}
	return 0;
}