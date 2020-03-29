#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAX_K 1000

bool available[MAX_K+1];

int denom_num;
long long denom[1000];

long long path[1000];

void test_and_store_result(int cur_depth)
{
    if(denom_num == 0)
    {
        memcpy(denom, path, cur_depth*sizeof(long long));
        denom_num = cur_depth;
    }
    else
    {
        for(int i = cur_depth-1; i >= 0; i--)
        {
            if(denom[i] < path[i])
                break;
            if(denom[i] > path[i])
            {
                memcpy(denom, path, cur_depth*sizeof(long long));
                break;
            }
        }
    }
}

bool id_dfs(int max_depth, int cur_depth, long long a, long long b)
{
    if(cur_depth == max_depth)
    {
        if(b%a == 0)
        {
            b /= a;
            a = 1;
        }
        if(a == 1 && (max_depth == 1 || b > path[max_depth-2]) && (b > MAX_K || available[b]))
        {
            path[max_depth-1] = b;
            test_and_store_result(cur_depth);
            return true;
        }
        return false;
    }
    int next = cur_depth == 1 ? 2 : path[cur_depth-2]+1;
    bool ret = false;
    while(b >= next*a)
        next++;
    while(true)
    {
        while(next <= MAX_K && !available[next])
            next++;
        if(next*a >= b*(max_depth-cur_depth+1))
            return ret;
        path[cur_depth-1] = next;
        ret = id_dfs(max_depth, cur_depth+1, a*next-b, b*next) || ret;
        next++;
    }
}

void output_result()
{
    for(int i = 0; i < denom_num-1; i++)
        printf("1/%d+", denom[i]);
    printf("1/%d\n", denom[denom_num-1]);
}

int main()
{
    int i, j, t, T, a, b, k;
    scanf("%d", &T);
    for(i = 1; i <= T; i++)
    {
        std::fill_n(available, MAX_K+1, true);
        scanf("%d%d%d", &a, &b, &k);
        for(j = 0; j < k; j++)
        {
            scanf("%d", &t);
            available[t] = false;
        }
        denom_num = 0;
        for(j = 1; ; j++)
            if(id_dfs(j, 1, a, b))
                break;
        printf("Case %d: %d/%d=", i, a, b);
        output_result();
    }
    return 0;
}
