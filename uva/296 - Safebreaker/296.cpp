#include <cstdio>
#include <cstring>

int n, g;
char gnum[10][5];
int gc[10], gm[10];

bool satisfy(char ans[], int s)
{
    int i, j, c, m;
    bool used[4];
    if(gc[s]+gm[s] > 4)
        return false;
    c = m = 0;
    for(i = 0; i < 4; i++)
    {
        used[i] = false;
        if(ans[i] == gnum[s][i])
        {
            ++c;
            used[i] = true;
        }
    }
    if(c != gc[s])
        return false;
    for(i = 0; i < 4; i++)
    {
        if(ans[i] == gnum[s][i])
            continue;
        for(j = 0; j < 4; j++)
        {
            if(i == j || used[j])
                continue;
            if(ans[i] == gnum[s][j])
            {
                ++m;
                used[j] = true;
                break;
            }
        }
    }
    return m == gm[s];
}

void solve()
{
    char ans[5] = {0}, p[5];
    int s;
    p[4] = 0;
    for(p[0] = '0'; p[0] <= '9'; ++p[0])
        for(p[1] = '0'; p[1] <= '9'; ++p[1])
            for(p[2] = '0'; p[2] <= '9'; ++p[2])
                for(p[3] = '0'; p[3] <= '9'; ++p[3])
                {
                    for(s = 0; s < g; s++)
                        if(!satisfy(p, s))
                            break;
                    if(s == g)
                    {
                        if(ans[0] == 0)
                            strcpy(ans, p);
                        else
                        {
                            puts("indeterminate");
                            return;
                        }
                    }
                }
    if(ans[0] == 0)
        puts("impossible");
    else
        puts(ans);
}

int main()
{
    int i;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &g);
        for(i = 0; i < g; i++)
            scanf("%s%d/%d", gnum[i], &gc[i], &gm[i]);
        solve();
    }
    return 0;
}

