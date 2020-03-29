#include <cstdio>
#include <cstring>

using namespace std;

int n;
int num[500];

inline int forward(int cur, int step)
{
	cur += step;
	if(cur >= n)
		cur -= n;
	return cur;
}

inline int backward(int cur, int step)
{
	cur -= step;
	if(cur < 0)
		cur += n;
	return cur;
}

int solve()
{
	int i, j, k, l, ans = 500, sum;
	bool flag[500];
	for(i = 0; i < n; i++)
	{
		memset(flag, false, n*sizeof(bool));
		sum = 0;
		l = backward(i, 1);
		for(j = i; j != l; j = forward(j, 1))
		{
			if(flag[j])
				continue;
			flag[j] = true;
			k = forward(i, num[j]);
			if(j == k)
				continue;
			while(!flag[k])
			{
				if(++sum >= ans)
					break;
				flag[k] = true;
				k = forward(i, num[k]);
			}
			if(sum >= ans)
				break;
		}
		if(sum < ans)
			ans = sum;
		memset(flag, false, n*sizeof(bool));
		sum = 0;
		l = forward(i, 1);
		for(j = i; j != l; j = backward(j, 1))
		{
			if(flag[j])
				continue;
			flag[j] = true;
			k = backward(i, num[j]);
			if(j == k)
				continue;
			while(!flag[k])
			{
				if(++sum >= ans)
					break;
				flag[k] = true;
				k = backward(i, num[k]);
			}
			if(sum >= ans)
				break;
		}
		if(sum < ans)
			ans = sum;
	}
	return ans;
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
		{
			scanf("%d", &num[i]);
			--num[i];
		}
		printf("%d\n", solve());
	}
	return 0;
}

