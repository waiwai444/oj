#include <stdio.h>
#include <string.h>
#include <math.h>

struct Point
{
    int x, y;
} com[8];
int com_num;

double dist[8][8];
int order[8];
double min_sum;

void recur(int depth, int cur_order[], double sum, bool used[])
{
    int i;
    double tmp_sum;
    for(i = 0; i < com_num; i++)
    {
        if(used[i])
            continue;
        tmp_sum = sum+dist[cur_order[depth-1]][i]+16.0;
        if(tmp_sum >= min_sum)
            continue;
        used[i] = true;
        cur_order[depth] = i;
        if(depth < com_num-1)
            recur(depth+1, cur_order, tmp_sum, used);
        else
        {
            memcpy(order, cur_order, com_num*sizeof(int));
            min_sum = tmp_sum;
        }
        used[i] = false;
    }
}

void brute_force()
{
    int i;
    int cur_order[8];
    bool used[8];
    min_sum = 10000.0;
    memset(used, false, sizeof(used));
    for(i = 0; i < com_num; i++)
    {
        cur_order[0] = i;
        used[i] = true;
        recur(1, cur_order, 0.0, used);
        used[i] = false;
    }
}

void output()
{
    static int tc = 1;
    printf("**********************************************************\n" "Network #%d\n", tc++);
    for(int i = 1; i < com_num; i++)
        printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", com[order[i-1]].x, com[order[i-1]].y, com[order[i]].x, com[order[i]].y, dist[order[i-1]][order[i]]+16.0);
    printf("Number of feet of cable required is %.2lf.\n", min_sum);
}

int main()
{
    int i, j;
    while(scanf("%d", &com_num), com_num)
    {
        for(i = 0; i < com_num; i++)
            scanf("%d%d", &com[i].x, &com[i].y);
        for(i = 0; i < com_num; i++)
            for(j = i+1; j < com_num; j++)
                dist[i][j] = dist[j][i] = sqrt((com[i].x-com[j].x)*(com[i].x-com[j].x)+(com[i].y-com[j].y)*(com[i].y-com[j].y));
        brute_force();
        output();
    }
    return 0;
}