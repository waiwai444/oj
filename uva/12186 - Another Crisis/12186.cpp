#include <algorithm>
#include <stdio.h>
#include <vector>

int N, T;

struct employee_t
{
    int boss;
    std::vector<int> subs;
} emp[100005];

int wcnt[100005];

bool cmp_subs(int i, int j)
{
    return wcnt[i] < wcnt[j];
}

void traverse(int cur)
{
    if(emp[cur].subs.size() == 0)
    {
        wcnt[cur] = 1;
        return;
    }
    int i, t = (int)emp[cur].subs.size()*T;
    if(t%100 == 0)
        t /= 100;
    else
        t = t/100+1;
    for(i = 0; i < emp[cur].subs.size(); ++i)
        traverse(emp[cur].subs[i]);
    std::sort(emp[cur].subs.begin(), emp[cur].subs.end(), cmp_subs);
    for(i = 0; i < t; ++i)
        wcnt[cur] += wcnt[emp[cur].subs[i]];
}

int main()
{
    int i;
    while(scanf("%d%d", &N, &T))
    {
        if(N == 0)
            break;
        emp[0].subs.clear();
        wcnt[0] = 0;
        for(i = 1; i <= N; ++i)
        {
            scanf("%d", &emp[i].boss);
            emp[i].subs.clear();
            emp[emp[i].boss].subs.push_back(i);
            wcnt[i] = 0;
        }
        traverse(0);
        printf("%d\n", wcnt[0]);
    }
    return 0;
}
