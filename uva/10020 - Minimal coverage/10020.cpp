#include <stdio.h>
#include <algorithm>

struct Line
{
	int l, r;
};

bool cmp(const Line &l1, const Line &l2)
{
	return l1.l < l2.l;
}

int m;
int line_num;
Line line[100000];
int result_num;
Line result[5000];

void solve()
{
	int i, left, cover, line_id;
	std::sort(line, line+line_num, cmp);
	left = 0;
	cover = 0;
	line_id = -1;
	result_num = 0;
	i = 0;
	while(i < line_num)
	{
		if(line[i].l > left)
		{
			if(line_id == -1)
			{
				result_num = 0;
				break;
			}
			result[result_num++] = line[line_id];
			left = cover;
			line_id = -1;
		}
		else if(line[i].l <= left)
		{
			if(line[i].r > cover)
			{
				cover = line[i].r;
				line_id = i;
				if(cover >= m)
				{
					result[result_num++] = line[line_id];
					break;
				}
			}
			i++;
		}
	}
	
	printf("%d\n", result_num);
	for(i = 0; i < result_num; i++)
		printf("%d %d\n", result[i].l, result[i].r);
}

int main()
{
	int tc, l, r;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &m);
		line_num = 0;
		while(scanf("%d%d", &l, &r), l != 0 || r != 0)
		{
			if(l == r || r <= 0 || l >= m)
				continue;
			line[line_num].l = l;
			line[line_num].r = r;
			line_num++;
		}
		solve();
		if(tc)
			printf("\n");
	}
	return 0;
}
