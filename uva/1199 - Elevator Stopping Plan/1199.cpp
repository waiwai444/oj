#include <stdio.h>
#include <string.h>

#define MAX_FLOOR 31

int mf;
bool floor[MAX_FLOOR], stop[MAX_FLOOR], cur_stop[MAX_FLOOR];

bool le_eq(int val)	// result less than or equal to this value
{
	int i, j, k, t;
	memset(cur_stop, false, sizeof(cur_stop));
	for(k = 1; k <= mf; k++)
		if(floor[k] && k*20 > val)
			break;
	i = k;
	t = 4*k;
	while(i <= mf)
	{
		if(t > val)
			return false;
		for(j = k; j <= i; j++)
		{
			if(floor[j] && t+4+(i+1-j)*20 > val)
			{
				cur_stop[i] = true;
				break;
			}
		}
		if(cur_stop[i])
		{
			for(j = i+1; j <= mf; j++)
			{
				if(floor[j] && t+(j-i)*20 > val)
				{
					k = j;
					break;
				}
			}
			if(j > mf)
				k = j;
			t += 10+(k-i)*4;
			i = k;
		}
		else
		{
			i++;
			t += 4;
		}
	}
	return true;
}

void solve()
{
	int min = 4, max = 410, cur, res = -1;
	while(min <= max)
	{
		cur = (min+max)/2;
		if(le_eq(cur))
		{
			res = cur;
			memcpy(stop, cur_stop, sizeof(stop));
			max = cur-1;
		}
		else
		{
			min = cur+1;
		}
	}
	int i, cnt = 0;
	for(i = 1; i <= mf; i++)
		if(stop[i])
			cnt++;
	printf("%d\n%d", res, cnt);
	for(i = 1; i <= mf; i++)
		if(stop[i])
			printf(" %d", i+1);
	printf("\n");
}

int main()
{
	int i, n, f;
	while(scanf("%d", &n), n)
	{
		memset(floor, false, sizeof(floor));
		mf = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%d", &f);
			floor[f-1] = true;
			if(f-1 > mf)
				mf = f-1;
		}
		solve();
	}
	return 0;
}