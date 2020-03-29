#include <stdio.h>
#include <string.h>

int n;
int row[10], col[10];
int cost[10][10], split[10][10];

void recur(int first, int last)
{
	int i, c;
	if(cost[first][last] >= 0)
		return;
	for(i = first; i < last; i++)
	{
		recur(first, i);
		recur(i+1, last);
		c = cost[first][i]+cost[i+1][last]+row[first]*col[i]*col[last];
		if(cost[first][last] == -1 || c < cost[first][last])
		{
			cost[first][last] = c;
			split[first][last] = i;
		}
	}
}

void get_cost()
{
	int i;
	memset(cost, -1, sizeof(cost));
	for(i = 0; i < n; i++)
		cost[i][i] = 0;
	recur(0, n-1);
}

void output(int first, int last)
{
	if(first == last)
	{
		printf("A%d", first+1);
		return;
	}
	int pos = split[first][last];
	printf("(");
	output(first, pos);
	printf(" x ");
	output(pos+1, last);
	printf(")");
}

int main()
{
	int i, tc = 0;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d%d", &row[i], &col[i]);
		get_cost();
		printf("Case %d: ", ++tc);
		output(0, n-1);
		printf("\n");
	}
	return 0;
}
