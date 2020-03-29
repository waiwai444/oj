#include <stdio.h>
#include <string.h>

#define MAX 32000

int n, num[100], target;
bool vis[100][MAX*2+1];
char op[100];

inline int index(int value)
{
	return value+MAX;
}

bool dfs(int cur, int value)
{
	if(cur == n)
		return value == target;
	int tmp = value+num[cur];
	if(tmp <= MAX && !vis[cur][index(tmp)])
	{
		vis[cur][index(tmp)] = true;
		op[cur] = '+';
		if(dfs(cur+1, tmp))
			return true;
	}
	tmp = value-num[cur];
	if(tmp >= -MAX && !vis[cur][index(tmp)])
	{
		vis[cur][index(tmp)] = true;
		op[cur] = '-';
		if(dfs(cur+1, tmp))
			return true;
	}
	tmp = value*num[cur];
	if(tmp >= -MAX && tmp <= MAX && !vis[cur][index(tmp)])
	{
		vis[cur][index(tmp)] = true;
		op[cur] = '*';
		if(dfs(cur+1, tmp))
			return true;
	}
	if(value%num[cur] == 0)
	{
		tmp = value/num[cur];
		if(!vis[cur][index(tmp)])
		{
			vis[cur][index(tmp)] = true;
			op[cur] = '/';
			if(dfs(cur+1, tmp))
				return true;
		}
	}
	return false;
}

void solve()
{
	if(n == 1)
	{
		if(num[0] == target)
			printf("%d=%d\n", target, target);
		else
			printf("NO EXPRESSION\n");
		return;
	}
	
	memset(vis, false, sizeof(vis));
	
	if(dfs(1, num[0]))
	{
		printf("%d", num[0]);
		for(int i = 1; i < n; i++)
			printf("%c%d", op[i], num[i]);
		printf("=%d\n", target);
	}
	else
		printf("NO EXPRESSION\n");
}

int main()
{
	int i, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &num[i]);
		scanf("%d", &target);
		solve();
	}
	return 0;
}
