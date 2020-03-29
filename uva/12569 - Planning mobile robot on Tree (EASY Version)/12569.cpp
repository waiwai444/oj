#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

int n, m, s, t;
int init_cfg, final_cfg;
std::vector<int> adj[16];
std::pair<int, int> tr[15][32768];
std::vector<std::pair<int, int> > steps;

int move(int u, int v, int cfg)
{
    return (cfg&~(1<<(u-1)))|(1<<(v-1));
}

bool bfs()
{
    int i, rob, cfg, u, v;
    std::pair<int, int> st;
    std::queue<std::pair<int, int> > Q;
    Q.push(std::make_pair(s, init_cfg));

    while(!Q.empty())
    {
        st = Q.front(), Q.pop();
        rob = st.first, cfg = st.second;
        for(u = 1; u <= n; ++u)
        {
            if((cfg&(1<<(u-1))) == 0)
                continue;
            for(i = 0; i < adj[u].size(); ++i)
            {
                v = adj[u][i];
                if(cfg&(1<<(v-1)))
                    continue;
                st.first = u == rob ? v : rob;
                st.second = move(u, v, cfg);
                std::pair<int, int> &p = tr[st.first-1][st.second];
                if(p.first == 0 && (st.first != s || st.second != init_cfg))
                {
                    p.first = u, p.second = v;
                    if(st.first == t)
                    {
                        final_cfg = st.second;
                        return true;
                    }
                    Q.push(st);
                }
            }
        }
    }

    return false;
}

void get_steps(int rob, int cfg)
{
    if(rob == s && cfg == init_cfg)
        return;
    int u = tr[rob-1][cfg].first;
    int v = tr[rob-1][cfg].second;
    int rob2 = v == rob ? u : rob;
    int cfg2 = move(v, u, cfg);
    get_steps(rob2, cfg2);
    steps.push_back(tr[rob-1][cfg]);
}

void solve()
{
    steps.clear();
    for(int i = 0; i < 15; ++i)
        for(int j = 0; j < 32768; ++j)
            tr[i][j].first = tr[i][j].second = 0;
    if(bfs())
        get_steps(t, final_cfg);
}

int main()
{
    int i, c, tc, u, v, obs;
    std::scanf("%d", &tc);
    for(c = 1; c <= tc; ++c)
    {
        for(i = 1; i <= n; ++i)
            adj[i].clear();
        std::scanf("%d%d%d%d", &n, &m, &s, &t);
        init_cfg = 1<<(s-1);
        for(i = 1; i <= m; ++i)
        {
            std::scanf("%d", &obs);
            init_cfg |= 1<<(obs-1);
        }
        for(i = 0; i < n-1; ++i)
        {
            std::scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        solve();
        std::printf("Case %d: %d\n", c, steps.size() > 0 ? (int)steps.size() : -1);
        for(i = 0; i < steps.size(); ++i)
            std::printf("%d %d\n", steps[i].first, steps[i].second);
        std::putchar('\n');
    }
    return 0;
}
