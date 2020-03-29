#include <stdio.h>
#include <algorithm>

int S[1000], ns, res;

bool solve()
{
	int i, j, k, t;
	if(ns < 4)
		return false;
	std::sort(&S[0], &S[ns]);
	for(t = ns-1; t >= 0; t--)
	{
		for(i = 0; i <= ns-3; i++)
		{
			if((S[t] >= 0 && i >= t) || (S[t] < 0 && S[i] >= 0))
				break;
			if(i == t)
				continue;
			j = i+1;
			k = ns-1;
			while(j < k)
			{
				if(j == t)
				{
					j++;
					continue;
				}
				if(k == t)
				{
					k--;
					continue;
				}
				if(S[i]+S[j]+S[k] == S[t])
				{
					res = S[t];
					return true;
				}
				else if(S[i]+S[j]+S[k] > S[t])
					k--;
				else
					j++;
			}
		}
	}
	return false;
}

int main()
{
	int i;
	while(scanf("%d", &ns), ns)
	{
		for(i = 0; i < ns; i++)
			scanf("%d", &S[i]);
		if(solve())
			printf("%d\n", res);
		else
			printf("no solution\n");
	}
	return 0;
}