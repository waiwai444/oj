#include <stdio.h>
#include <vector>

#define MAX 20000

int N;
std::vector<int> adj[10001];
int min[10001][3];

void traverse(int r, int p)
{
    int s = 0, m, c = 0;
    min[r][0] = 0;
    min[r][1] = MAX;
    min[r][2] = 1;
    for(auto i : adj[r])
    {
        if(i != p)
        {
            traverse(i, r);
            s += min[i][1];
            ++c;
        }
    }
    if(c == 0)
        return;
    min[r][0] = s;
    for(auto i : adj[r])
    {
        if(i != p)
        {
            m = min[i][2];
            m += s-min[i][1];
            if(m < min[r][1])
                min[r][1] = m;
            if(min[i][0] < min[i][2])
                min[r][2] += min[i][0];
            else
                min[r][2] += min[i][2];
        }
    }
}

int main()
{
    int i, u, v;
    while(scanf("%d", &N))
    {
        for(i = 1; i <= N; ++i)
            adj[i].clear();
        for(i = 0; i < N-1; ++i)
        {
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        scanf("%d", &u);
        if(N == 1)
            puts("1");
        else
        {
            traverse(1, -1);
            printf("%d\n", min[1][1] < min[1][2] ? min[1][1] : min[1][2]);
        }
        if(u == -1)
            break;
    }
    return 0;
}
