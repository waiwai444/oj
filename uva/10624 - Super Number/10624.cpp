#include <stdio.h>
#include <string.h>

char result[30][30][30];
int n, m;
char cur_int[30];

void print_result(int tc)
{
	printf("Case %d: ", tc);
	for(int i = 0; i < m; i++)
		printf("%d", result[n][m][i]);
	printf("\n");
}

void mark_unsolvable()
{
	for(int i = m; i < 30; i++)
		result[n][i][0] = (char)-1;
}

bool divisible(int cur)
{
	int rem = 0;
	for(int i = 0; i < cur; i++)
		rem = (rem*10+cur_int[i])%cur;
	return rem == 0;
}

bool dfs(int cur)
{
	if(cur > m)
	{
		memcpy(result[n][m], cur_int, sizeof(cur_int));
		return true;
	}
	else
	{
		while(cur_int[cur-1] < 10)
		{
			if(cur < n)
			{
				if(dfs(cur+1))
					return true;
			}
			else
			{
				if(divisible(cur))
				{
					if(result[n][cur][0] == 0)
						memcpy(result[n][cur], cur_int, sizeof(cur_int));
					if(dfs(cur+1))
						return true;
				}
			}
			cur_int[cur-1]++;
		}
	}
	
	cur_int[cur-1] = 0;
	return false;
}

void solve(int tc)
{
	int i, j;
	if(result[n][m][0] == 0)
	{
		memset(cur_int, 0, sizeof(cur_int));
		cur_int[0] = 1;
		for(j = m-1; j > n; j--)
			if(result[n][j][0] != 0)
				break;
		if(j > n)
		{
			for(i = 0; i < j; i++)
				cur_int[i] = result[n][j][i];
			if(!dfs(1))
				mark_unsolvable();
		}
		else
		{
			if(!dfs(1))
				mark_unsolvable();
		}
	}
	if(result[n][m][0] == (char)-1)
		printf("Case %d: -1\n", tc);
	else if(result[n][m][0] != 0)
		print_result(tc);
}

int main()
{
	int i, tc;
	scanf("%d", &tc);
	for(i = 1; i <= tc; i++)
	{
		scanf("%d%d", &n, &m);
		solve(i);
	}
	return 0;
}