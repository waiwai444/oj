#include <stdio.h>

int m, k;
int book[500];
int part[500];

bool candidate_min(long long value)
{
	int i, j;
	long long sum;
	for(i = 0, j = 0; i < k && j < m; i++)
	{
		sum = 0;
		while(j < m)
		{
			sum += book[j];
			if(sum < value)
				j++;
			else
			{
				if(sum == value)
					j++;
				break;
			}
		}
	}
	return j >= m;
}

long long search_min(long long tot)
{
	long long low = 1, high = tot, mid, min;
	while(low <= high)
	{
		mid = (low+high)/2;
		if(candidate_min(mid))
		{
			min = mid;
			high = mid-1;
		}
		else
		{
			low = mid+1;
		}
	}
	return min;
}

void get_partition(long long ub)
{
	int i, cur = k;
	long long sum = 0;
	for(i = m-1; i >= 0; i--)
	{
		sum += book[i];
		if(sum <= ub && i >= cur-1)
			part[i] = cur;
		else
		{
			part[i] = --cur;
			sum = book[i];
		}
	}
}

void print_result()
{
	printf("%d", book[0]);
	for(int i = 1; i < m; i++)
	{
		if(part[i] != part[i-1])
			printf(" /");
		printf(" %d", book[i]);
	}
	printf("\n");
}

void solve()
{
	long long tot = 0;
	for(int i = 0; i < m; i++)
		tot += book[i];
	long long min = search_min(tot);
	get_partition(min);
	print_result();
}

int main()
{
	int i, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &m, &k);
		for(i = 0; i < m; i++)
			scanf("%d", &book[i]);
		solve();
	}
	return 0;
}
