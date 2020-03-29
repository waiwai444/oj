#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

#define INF 0x3f3f3f3f

int n, m;
int tm[100], sp[100], sa[100], tp[100], ta[100];
bool vis[1<<20];

void parse(const char *buf, int *p, int *a)
{
    int f = 1;
    *p = *a = 0;
    while(*buf)
    {
        if(*buf == '+')
            *p |= f;
        else if(*buf == '-')
            *a |= f;
        ++buf;
        f <<= 1;
    }
}

inline bool appliable(int v, int p, int a)
{
	return (v&p) == p && (~v&a) == a;
}

inline int next(int v, int p, int a)
{
    return v&~a|p;
}

int solve()
{
    int i, adj;
    typedef std::pair<int, int> node_t;
    std::priority_queue<node_t, std::vector<node_t>, std::greater<node_t> > q;
    std::pair<int, int> p;
    memset(vis, false, (1<<n)*sizeof(bool));
    q.push(std::make_pair(0, (1<<n)-1));
    while(!q.empty())
    {
        p = q.top();
        q.pop();
        if(p.second == 0)
            return p.first;
        if(vis[p.second])
            continue;
        vis[p.second] = true;
        for(i = 0; i < m; i++)
        {
            if(!appliable(p.second, sp[i], sa[i]))
                continue;
            adj = next(p.second, tp[i], ta[i]);
            if(vis[adj])
                continue;
            q.push(std::make_pair(p.first+tm[i], adj));
        }
    }
    return -1;
}

int main()
{
    int i, ans, c = 0;
    char buf[21];
    while(scanf("%d%d", &n, &m), n)
    {
        for(i = 0; i < m; i++)
        {
            scanf("%d%20s", &tm[i], buf);
            parse(buf, &sp[i], &sa[i]);
            scanf("%20s", buf);
            parse(buf, &tp[i], &ta[i]);
        }
        ans = solve();
        printf("Product %d\n", ++c);
        if(ans >= 0)
            printf("Fastest sequence takes %d seconds.\n\n", ans);
        else
            printf("Bugs cannot be fixed.\n\n");
    }
    return 0;
}
