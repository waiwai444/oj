#include <stdio.h>
#include <algorithm>

#define MAXN 2000

struct Point
{
	int x, y;	// x: vertical, y: horizontal
};

int length, width;
int n;
Point tree[MAXN];

bool cmp_y(const Point& p1, const Point& p2)
{
	return p1.y < p2.y;
}

bool cmp_x(int i, int j)
{
	return tree[i].x < tree[j].x;
}

int max_rec()
{
	int i, j, lower_bound, upper_bound, max_area, area;
	int sorted_by_x[MAXN];
	
	if(n == 0)
		return length*width;
	
	std::sort(tree, tree+n, cmp_y);
	
	for(i = 0; i < n; i++)
		sorted_by_x[i] = i;
	std::sort(sorted_by_x, sorted_by_x+n, cmp_x);
	
	// for those rectangles with their left and right borders reach the borders of the whole area
	int height, max_height = tree[sorted_by_x[0]].x;
	for(i = 1; i < n; i++)
		if((height = tree[sorted_by_x[i]].x-tree[sorted_by_x[i-1]].x) > max_height)
			max_height = height;
	if((height = length-tree[sorted_by_x[n-1]].x) > max_height)
		max_height = height;
	max_area = max_height*width;
	
	// for those rectangles with their left or right border blocked by some tree
	for(i = 0; i < n; i++)
	{
		lower_bound = 0;
		upper_bound = length;
		for(j = i+1; j < n; j++)
		{
			if(tree[j].y == tree[i].y || tree[j].x <= lower_bound || tree[j].x >= upper_bound)
				continue;
			
			if((area = (tree[j].y-tree[i].y)*(upper_bound-lower_bound)) > max_area)
				max_area = area;
			
			if(tree[j].x >= tree[i].x)
				upper_bound = tree[j].x;
			if(tree[j].x <= tree[i].x)
				lower_bound = tree[j].x;
			if(lower_bound == upper_bound)
				break;
		}
		// to right border
		if(upper_bound > lower_bound && (area = (width-tree[i].y)*(upper_bound-lower_bound)) > max_area)
			max_area = area;
		// to left border
		lower_bound = 0;
		upper_bound = length;
		for(j = i-1; j>=0; j--)
		{
			if(tree[j].y == tree[i].y || tree[j].x <= lower_bound || tree[j].x >= upper_bound)
				continue;
			if(tree[j].x <= tree[i].x)
				lower_bound = tree[j].x;
			if(tree[j].x >= tree[i].x)
				upper_bound = tree[j].x;
			if(lower_bound == upper_bound)
				break;
		}
		if(upper_bound > lower_bound && (area = tree[i].y*(upper_bound-lower_bound)) > max_area)
			max_area = area;
	}
	
	return max_area;
}

int main()
{
	int i, j, tc, k, x, y, dx, dy, tx, ty;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &length, &width);
		n = 0;
		while(scanf("%d", &k), k)
		{
			if(k == 1)
				scanf("%d%d", &x, &y);
			else
				scanf("%d%d%d%d", &x, &y, &dx, &dy);
			for(i = 0; i < k; i++)
			{
				tx = x+i*dx;
				ty = y+i*dy;
				if(tx == 0 || tx == length || ty == 0 || ty == width)
					continue;

				tree[n].x = tx;
				tree[n].y = ty;
				n++;
			}
		}
		printf("%d\n", max_rec());
	}
	return 0;
}
