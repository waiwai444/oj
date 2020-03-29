#include <stdio.h>
#include <string.h>

#define MAX_TOPIC 1000
#define MAX_LEC MAX_TOPIC
#define UNVISITED 0x3f3f3f3f
#define INFEASIBLE (UNVISITED-1)

int n, L, C;
int t[MAX_TOPIC+1];
int dp[MAX_LEC+1][MAX_TOPIC+1];
int last_topic[MAX_TOPIC+1];	// The last topic that can be in the same lecture when the current topic is the first one in this lecture.
int accum_time[MAX_TOPIC+1];
int min_ln, min_di;

int calc_di(int free_time)
{
	if(free_time == 0)
		return 0;
	if(free_time <= 10)
		return -C;
	return (free_time-10)*(free_time-10);
}

inline void check_result(int di)
{
	if(di < min_di)
		min_di = di;
}

void get_min_lec_num()
{
	int i, sum = 0;
	min_ln = 1;
	for(i = 1; i <= n; i++)
	{
		sum += t[i];
		if(sum > L)
		{
			sum = t[i];
			min_ln++;
		}
	}
	min_di = UNVISITED;
}

int recur(int cur_lec, int cur_topic, int prev_di)
{
	int *cdp = &dp[cur_lec][cur_topic];
	if(*cdp != UNVISITED)
	{
		if(*cdp != INFEASIBLE)
			check_result(prev_di+*cdp);
		return *cdp;
	}

	*cdp = INFEASIBLE;
	int i = last_topic[cur_topic];
	if(i == n)	// cur_lec == min_ln
	{
		*cdp = calc_di(L-(accum_time[i]-accum_time[cur_topic-1]));
		check_result(prev_di+*cdp);
	}
	else if(cur_lec < min_ln)
	{
		int di = calc_di(L-(accum_time[i]-accum_time[cur_topic-1]));
		di += recur(cur_lec+1, i+1, prev_di+di);
		if(di < INFEASIBLE)
		{
			*cdp = di;
			for(i--; i >= cur_topic; i--)
			{
				di = calc_di(L-(accum_time[i]-accum_time[cur_topic-1]));
				di += recur(cur_lec+1, i+1, prev_di+di);
				if(di >= INFEASIBLE)
					break;
				if(di < *cdp)
					*cdp = di;
			}
		}
	}
	return *cdp;
}

void solve()
{
	int i, j;
	memset(dp, 0x3f, sizeof(dp));
	for(i = j = 1; i <= n; i++)
	{
		accum_time[i] = accum_time[i-1]+t[i];
		while(accum_time[i]-accum_time[j-1] > L)
			last_topic[j++] = i-1;
	}
	while(j <= n)
		last_topic[j++] = n;
	get_min_lec_num();
	recur(1, 1, 0);
}

int main()
{
	int i, tc = 0;
	while(scanf("%d", &n), n)
	{
		scanf("%d%d", &L, &C);
		for(i = 1; i <= n; i++)
			scanf("%d", &t[i]);
		solve();
		if(tc)
			printf("\n");
		printf("Case %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n", ++tc, min_ln, min_di);
	}
	return 0;
}
