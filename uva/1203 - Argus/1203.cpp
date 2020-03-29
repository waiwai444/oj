#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

int n, k;
int qnum[1000];
int period[3001];

int main()
{
    int i, pr;
    char str[10];
    typedef std::pair<int, int> pii;
    pii p;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    while(scanf("%s", str) != EOF)
    {
        n = 0;
        while(str[0] != '#')
        {
            scanf("%d%d%s", &qnum[n], &pr, str);
            period[qnum[n++]] = pr;
        }
        scanf("%d", &k);

        while(!q.empty())
            q.pop();
        for(i = 0; i < n; i++)
            q.push(std::make_pair(period[qnum[i]], qnum[i]));
        i = 0;
        while(!q.empty())
        {
            p = q.top(), q.pop();
            printf("%d\n", p.second);
            if(++i >= k)
                break;
            q.push(std::make_pair(p.first+period[p.second], p.second));
        }
    }
    return 0;
}

