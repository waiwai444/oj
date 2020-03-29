#include <cstdio>

int ans[1001];
char flag[1001]; // it's sufficient
int pw[20];
int m, cnt;

bool check_ans(int n, int d)
{
    if(n > 0 && n <= 1000 && ans[n] < 0)
    {
        ans[n] = d;
        ++cnt;
        while(m < 1000 && ans[m+1] >= 0)
            ++m;
    }
    return cnt >= 1000;
}

bool dfs(int curd, int maxd)
{
    int i, c, n;
    c = pw[curd];
    if(curd == maxd)
        return check_ans(c, maxd);
    if(c<<(maxd-curd) <= m)
        return false;
    for(i = curd; i >= 0; --i)
    {
        n = c+pw[i];
        if(n <= 1000 && !flag[n])
        {
            flag[n] = 1;
            pw[curd+1] = n;
            if(dfs(curd+1, maxd))
                return true;
            flag[n] = 0;
        }
        n = c-pw[i];
        if(n > 0 && !flag[n])
        {
            flag[n] = 1;
            pw[curd+1] = n;
            if(dfs(curd+1, maxd))
                return true;
            flag[n] = 0;
        }
    }
    return false;
}

void iddfs()
{
    int maxd = 1;
    m = 1;
    flag[1] = 1;
    pw[0] = 1;
    for(;; ++maxd)
        if(dfs(0, maxd))
            return;
}

int main()
{
    int n;

    for(int i = 2; i <= 1000; ++i)
        ans[i] = -1;
    cnt = 1;
    iddfs();

    while(std::scanf("%d", &n), n)
    {
        std::printf("%d\n", ans[n]);
    }
    return 0;
}
