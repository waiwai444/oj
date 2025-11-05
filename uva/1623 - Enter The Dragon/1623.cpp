#include <queue>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <vector>

#define MAXN 1000010
#define MAXM MAXN

int n, m;
int t[MAXM];
int drink[MAXM];
char lake[MAXN];
std::pair<int, int> standby[MAXN];
int sb_next[MAXM];

struct comparator
{
    bool operator()(std::pair<int, int> &p1, std::pair<int, int> &p2)
    {
        return p1.first > p2.first;
    }
};

void solve()
{
    int i, j, k = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comparator> pq;
    memset(lake, 1, (n + 1) * sizeof(char));
    memset(drink, 0, m * sizeof(int));
    for(i = 1; i <= n; ++i)
        standby[i].first = standby[i].second = -1;
    for(j = 0; t[j] == 0 && j < m; ++j);
    for(i = 0; i < j; ++i)
    {
        if(t[i] == 0)
        {
            if(pq.size())
            {
                drink[i] = pq.top().second;
                lake[pq.top().second] = 0;
                pq.pop();
                --k;
            }
            else
            {
                if(j < m)
                {
                    drink[i] = t[j];
                    lake[t[j]] = 0;
                    for(++j; j < m && (lake[t[j]] == 0 || t[j] == 0); ++j)
                    {
                        if(lake[t[j]] == 0)
                        {
                            if(standby[t[j]].first == -1)
                            {
                                standby[t[j]].first = standby[t[j]].second = j;
                            }
                            else
                            {
                                sb_next[standby[t[j]].second] = j;
                                standby[t[j]].second = j;
                            }
                            sb_next[j] = -1;
                            ++k;
                        }
                    }
                }
            }
        }
        else
        {
            if(lake[t[i]])
                break;
            lake[t[i]] = 1;
            if(standby[t[i]].first != -1)
            {
                pq.push(std::make_pair(standby[t[i]].first, t[i]));
                standby[t[i]].first = sb_next[standby[t[i]].first];
            }
        }
    }
    if(k || (i < m && i >= j))
        puts("NO");
    else
    {
        printf("YES\n%d", drink[0]);
        for(i = 1; i < m; ++i)
            if(t[i] == 0)
                printf(" %d", drink[i]);
        putchar('\n');
    }
}

int main()
{
    int i, Z;
    scanf("%d", &Z);
    while(Z--)
    {
        scanf("%d%d", &n, &m);
        for(i = 0; i < m; ++i)
        {
            scanf("%d", &t[i]);
        }
        solve();
    }
    return 0;
}
