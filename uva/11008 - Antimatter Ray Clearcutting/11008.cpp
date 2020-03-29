#include <stdio.h>
#include <string.h>
#include <queue>

int n, m;

struct tree_t
{
	int x, y;
} trees[16];

struct line_t
{
	int a, b, c;
	int flag;
	int nt;
} lines[120];
int line_num;

struct queue_elem_t
{
	int flag;
	int nt;
	int nl;
};

bool visited[65536];

void get_lines()
{
	int i, j, k, l;
	int collinear[16], nc;
	bool tree_pair[16][16];
	line_num = 0;
	memset(lines, 0, sizeof(lines));
	memset(tree_pair, false, sizeof(tree_pair));
	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)
			if(!tree_pair[i][j])
			{
				lines[line_num].a = trees[j].y-trees[i].y;
				lines[line_num].b = trees[i].x-trees[j].x;
				lines[line_num].c = trees[j].x*trees[i].y-trees[i].x*trees[j].y;
				lines[line_num].flag |= (1<<i) | (1<<j);
				collinear[0] = i;
				collinear[1] = j;
				nc = 2;
				for(k = j+1; k < n; k++)
				{
					if(lines[line_num].a*trees[k].x+lines[line_num].b*trees[k].y+lines[line_num].c == 0)
					{
						lines[line_num].flag |= (1<<k); 
						collinear[nc++] = k;
					}
				}
				for(k = 0; k < nc; k++)
					for(l = k+1; l < nc; l++)
						tree_pair[collinear[k]][collinear[l]] = tree_pair[collinear[l]][collinear[k]] = true;
				lines[line_num].nt = nc;
				++line_num;
			}
}

int count(int flag)
{
	int i, c = 0;
	for(i = 0; i < 16; i++)
		if(flag & (1<<i))
			++c;
	return c;
}

int bfs()
{
	int i;
	std::queue<queue_elem_t> q;
	queue_elem_t e, e2;
	memset(visited, false, sizeof(visited));
	for(i = 0; i < line_num; i++)
	{
		e.flag = lines[i].flag;
		e.nt = lines[i].nt;
		if(e.nt >= m)
			return 1;
		e.nl = 1;
		visited[e.flag] = true;
		q.push(e);
	}
	while(!q.empty())
	{
		e = q.front();
		q.pop();
		for(i = 0; i < line_num; i++)
		{
			e2 = e;
			e2.flag |= lines[i].flag;
			if(visited[e2.flag])
				continue;
			e2.nt = count(e2.flag);
			++e2.nl;
			if(e2.nt >= m)
				return e2.nl;
			visited[e2.flag] = true;
			q.push(e2);
		}
	}
	return -1;
}

int main()
{
	int i, tc, c;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%d%d", &n, &m);
		for(i = 0; i < n; i++)
			scanf("%d%d", &trees[i].x, &trees[i].y);
		get_lines();
		if(c > 1)
			printf("\n");
		printf("Case #%d:\n%d\n", c, n == 1 ? 1 : bfs());
	}
	return 0;
}
