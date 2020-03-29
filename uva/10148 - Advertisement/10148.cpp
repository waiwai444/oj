#include <stdio.h>
#include <string.h>
#include <algorithm>

int jogger_num, min_ad;
struct Jogger
{
	int first, last;
} jogger[1000];

int ad_num;
bool ad[20001];

#define billboard_idx(x) (x+10000)

bool cmp_jogger(const Jogger &j1, const Jogger &j2)
{
	return j1.last < j2.last;
}

int main()
{
	int i, j, tc, a, b, n;
	bool first = true;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &min_ad, &n);
		ad_num = jogger_num = 0;
		memset(ad, false, sizeof(ad));
		for(i = 0; i < n; i++)
		{
			scanf("%d%d", &a, &b);
			if(a > b)
			{
				int tmp = a;
				a = b;
				b = tmp;
			}
			if(b-a+1 <= min_ad)
			{
				for(j = a; j <= b; j++)
					if(!ad[billboard_idx(j)])
					{
						ad[billboard_idx(j)] = true;
						ad_num++;
					}
			}
			else
			{
				jogger[jogger_num].first = a;
				jogger[jogger_num++].last = b;
			}
		}
		std::sort(jogger, jogger+jogger_num, cmp_jogger);
		
		for(i = 0; i < jogger_num; i++)
		{
			int count = 0;
			for(j = jogger[i].first; j <= jogger[i].last; j++)
				if(ad[billboard_idx(j)])
					count++;
			while(count < min_ad)
			{
				j--;
				if(!ad[billboard_idx(j)])
				{
					ad[billboard_idx(j)] = true;
					ad_num++;
					count++;
				}
			}
		}
		
		if(first)
			first = false;
		else
			printf("\n");
		printf("%d\n", ad_num);
		for(i = -10000; i <= 10000; i++)
			if(ad[billboard_idx(i)])
				printf("%d\n", i);
	}
	return 0;
}
