#include <algorithm>
#include <stdio.h>

int n;

struct task_t
{
    int r, d;
} task[100001];

bool cmp(task_t &t1, task_t &t2)
{
    return t1.r < t2.r || (t1.r == t2.r && t1.d < t2.d);
}

void solve()
{
    int i, j, p, idle = 0;
    std::sort(&task[0], &task[n], cmp);
    for(i = 0; i < n; ++i)
    {
        p = task[i].d;
        for(j = i + 1; j < n; ++j)
        {
            if(task[j].r > p)
                break;
            if(task[j].d > p)
                ++p;
        }
        i = j - 1;
        ++idle;
    }
    printf("%d\n", idle - 1);
}

int main()
{
    int i, T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
        {
            scanf("%d%d", &task[i].r, &task[i].d);
        }
        solve();
    }
    return 0;
}
