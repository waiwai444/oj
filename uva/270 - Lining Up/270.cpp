#include <stdio.h>
#include <string.h>
#include <algorithm>

struct Point
{
	int x, y;
};

int n;
Point pt[700], slope[700];

inline bool cmp_slope(const Point &p1, const Point &p2)
{
	if((p1.x == 0 && p2.x == 0) || (p1.x == 0 && p2.x != 0))
		return false;
	else if(p1.x != 0 && p2.x == 0)
		return true;
	else if((p1.x > 0 && p2.x > 0) || (p1.x < 0 && p2.x < 0))
		return p1.y*p2.x < p2.y*p1.x;
	else
		return p1.y*p2.x > p2.y*p1.x;
}

int solve()
{
	int i, j, k, max = 0, cur;
	for(i = 0; i < n; i++)
	{
		for(k = 0, j = i+1; j < n; j++)
		{
			slope[k].x = pt[j].x-pt[i].x;
			slope[k].y = pt[j].y-pt[i].y;
			k++;
		}
		std::sort(slope, slope+k, cmp_slope);
		cur = 1;
		for(j = 0; j < k; j++)
		{
			if(j > 0 && cmp_slope(slope[j-1], slope[j]))
			{
				if(cur > max)
					max = cur;
				cur = 1;
			}
			cur++;
		}
		if(cur > max)
			max = cur;
	}
	return max;
}

int main()
{
	int tc;
	char line[100];
	scanf("%d", &tc);
	fgets(line, sizeof(line), stdin);
	fgets(line, sizeof(line), stdin);
	while(tc--)
	{
		n = 0;
		while(fgets(line, sizeof(line), stdin) && line[0] != '\n')
		{
			sscanf(line, "%d%d", &pt[n].x, &pt[n].y);
			n++;
		}
		printf("%d\n", solve());
		if(tc)
			printf("\n");
	}
	return 0;
}
