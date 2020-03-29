#include <stdio.h>
#include <stdlib.h>

#define MAX_PKG_NUM 100000

int cap, npack;
struct pack_t
{
    int x, y;
    int w;
} pkg[MAX_PKG_NUM+1];

int dp[MAX_PKG_NUM+1];
int dist_all[MAX_PKG_NUM+1];
int dist_dir[MAX_PKG_NUM+1];
int w_sum[MAX_PKG_NUM+1];
int q[MAX_PKG_NUM];

int solve()
{
    int i, j, head, tail;
    for(i = 1; i <= npack; i++)
    {
        dist_all[i] = dist_all[i-1]+abs(pkg[i].x-pkg[i-1].x)+abs(pkg[i].y-pkg[i-1].y);
        dist_dir[i] = pkg[i].x+pkg[i].y;
		w_sum[i] = pkg[i].w+w_sum[i-1];
    }
	head = tail = 0;
    for(i = 1; i <= npack; i++)
    {
		while(head < tail && w_sum[i]-w_sum[q[head]] > cap)
			++head;
		dp[i] = dp[q[head]]+dist_dir[q[head]+1]+(dist_all[i]-dist_all[q[head]+1])+dist_dir[i];
		if(i == npack)
			break;
		while(head <= tail && dp[i]+dist_dir[i+1] < dp[q[tail]]+dist_dir[q[tail]+1]+dist_all[i+1]-dist_all[q[tail]+1])
			--tail;
		q[++tail] = i;
    }
    return dp[npack];
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &cap, &npack);
        for(i = 1; i <= npack; i++)
            scanf("%d%d%d", &pkg[i].x, &pkg[i].y, &pkg[i].w);
        printf("%d\n", solve());
        if(tc)
            printf("\n");
    }
    return 0;
}
