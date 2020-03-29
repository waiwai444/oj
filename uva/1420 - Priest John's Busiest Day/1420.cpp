#include <cstdio>
#include <algorithm>

int n;
struct task_t { int s, t, m; } task[100000];

bool cmp_task(const task_t &t1, const task_t &t2)
{
    return t1.m < t2.m;
}

bool solve()
{
    int i, t = 0;
    std::sort(&task[0], &task[n], cmp_task);
    for(i = 0; i < n; i++)
    {
        if(t < task[i].s)
            t = task[i].m;
        else
        {
            t += task[i].m-task[i].s;
            if(t > task[i].t)
                return false;
        }
    }
    return true;
}

int main()
{
    int i;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%d%d", &task[i].s, &task[i].t);
            task[i].m = (task[i].s+task[i].t)/2+1;
        }
        if(solve())
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

