#include <stdio.h>

int s;
int nice[20000];
int start, end, max;

void solve()
{
	int i, cur_max = 0, cur_start = 0;
	max = 0;
	for(i = 0; i < s-1; i++)
	{
		if(cur_max+nice[i] < nice[i])
		{
			cur_max = nice[i];
			cur_start = i;
		}
		else
		{
			cur_max += nice[i];
		}
		if(cur_max > max)
		{
			max = cur_max;
			start = cur_start;
			end = i+1;
		}
		else if(cur_max == max && i-cur_start > end-start)
		{
			start = cur_start;
			end = i+1;
		}
	}
}

int main()
{
	int i, c, tc;
	bool no_nice;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%d", &s);
		no_nice = true;
		for(i = 0; i < s-1; i++)
		{
			scanf("%d", &nice[i]);
			if(nice[i] > 0 && no_nice)
				no_nice = false;
		}
		if(no_nice)
			printf("Route %d has no nice parts\n", c);
		else
		{
			solve();
			printf("The nicest part of route %d is between stops %d and %d\n", c, start+1, end+1);
		}
	}
	return 0;
}