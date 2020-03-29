#include <cstdio>
#include <cstring>

int n;
unsigned all, awake[2];
bool adj[26][26];

int solve()
{
    int i, j, c, y = 0, t = 0;
    for(i = 0, c = 0; i < 26; i++)
        if(all&(1<<i))
            ++c;
    if(c < n)
        return -1;
    while(y <= 26 && awake[t] != all)
    {
        awake[1-t] = awake[t];
        for(i = 0; i < 26; i++)
        {
            if(!(all&(1<<i)) || (awake[t]&(1<<i)))
                continue;
            c = 0;
            for(j = 0; j < 26; j++)
            {
                if(!(all&(1<<i)))
                    continue;
                if(adj[i][j] && (awake[t]&(1<<j)))
                    ++c;
                if(c >= 3)
                    break;
            }
            if(c >= 3)
                awake[1-t] |= 1<<i;
        }
        t = 1-t;
        ++y;
    }
    return y <= 26 ? y : -1;
}

int main()
{
    int i, m, u, v;
    char line[4];
    while(scanf("%d%d%s", &n, &m, line) != EOF)
    {
        awake[0] = awake[1] = 0;
        for(i = 0; i < 3; i++)
            awake[0] |= 1<<(line[i]-'A');
        all = awake[0];
        memset(adj, false, sizeof(adj));
        for(i = 0; i < m; i++)
        {
            scanf("%s", line);
            u = line[0]-'A', v = line[1]-'A';
            adj[u][v] = adj[v][u] = true;
            all |= (1<<u)|(1<<v);
        }
        int ans = solve();
        if(ans >= 0)
            printf("WAKE UP IN, %d, YEARS\n", ans);
        else
            puts("THIS BRAIN NEVER WAKES UP");
    }
    return 0;
}

