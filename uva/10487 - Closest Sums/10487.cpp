#include <stdio.h>
#include <algorithm>

int n, m, num[1000], query;

int search()
{
	int i = 0, j = n-1, less = 0, more = 0, t;
	bool f1 = false, f2 = false;
	while(i < j && num[i] != num[j])
	{
		t = num[i]+num[j];
		if(t > query)
		{
			if(!f1)
			{
				f1 = true;
				more = t;
			}
			else if(more > t)
				more = t;
			do
			{
				j--;
			} while(i < j && num[j] == num[j+1]);
		}
		else if(t < query)
		{
			if(!f2)
			{
				f2 = true;
				less = t;
			}
			else if(less < t)
				less = t;
			do
			{
				i++;
			} while(i < j && num[i] == num[i-1]);
		}
		else
			return t;
	}
	if(!f1)
		return less;
	if(!f2)
		return more;
	if(more-query > query-less)
		return less;
	else
		return more;
}

int main()
{
	int i, tc = 0;
	while(scanf("%d", &n), n)
	{
		printf("Case %d:\n", ++tc);
		for(i = 0; i < n; i++)
			scanf("%d", &num[i]);
		std::sort(num, num+n);
		scanf("%d", &m);
		for(i = 0; i < m; i++)
		{
			scanf("%d", &query);
			printf("Closest sum to %d is %d.\n", query, search());
		}
	}
	return 0;
}