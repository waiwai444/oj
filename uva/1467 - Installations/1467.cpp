#include <cstdio>
#include <algorithm>

int n;
struct job_t { int s, d; } jobs[500];
int end[500];

bool cmp_job(const job_t &j1, const job_t &j2)
{
    return j1.d < j2.d;
}

inline void update_max2(int d, int *m1, int *m2)
{
    if(d < 0)
        d = 0;
    if(d > *m1)
        *m2 = *m1, *m1 = d;
    else if(d > *m2)
        *m2 = d;
}

int solve()
{
    int i, j, d, m1, m2, p, t1, t2, ans;
    if(n == 1)
        return std::max(jobs[0].s-jobs[0].d, 0);
    std::sort(&jobs[0], &jobs[n], cmp_job);
    end[0] = jobs[0].s;
    for(i = 1; i < n; i++)
        end[i] = end[i-1]+jobs[i].s;
    m1 = m2 = -1;
    for(i = 0; i < n; i++)
        update_max2(end[i]-jobs[i].d, &m1, &m2);
    if(m1 == 0 || m2 == 0)
        return m1;
    for(i = n-1; i >= 0; i--)
    {
        d = std::max(end[i]-jobs[i].d, 0);
        if(d == m1 || d == m2)
        {
            p = i;
            break;
        }
    }
    ans = m1+m2;
    t1 = t2 = -1;
    for(i = p+1; i < n; i++)
        update_max2(end[i]-jobs[i].d, &t1, &t2);
    for(i = 0; i < p; i++)
    {
        if(i > 0)
            update_max2(end[i-1]-jobs[i-1].d, &t1, &t2);
        m1 = t1, m2 = t2;
        for(j = i+1; j <= p; j++)
            update_max2(end[j]-jobs[i].s-jobs[j].d, &m1, &m2);
        update_max2(end[p]-jobs[i].d, &m1, &m2);
        if(m1+m2 < ans)
            ans = m1+m2;
    }
    return ans;
}

int main()
{
    int t, i;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d%d", &jobs[i].s, &jobs[i].d);
        printf("%d\n", solve());
    }
    return 0;
}

