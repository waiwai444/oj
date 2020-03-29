#include <cstdio>

int w[6], h[6];

bool solve()
{
    int i, j, t, x, y, z;
    for(i = 0; i < 6; i++)
        if(w[i] > h[i])
            t = w[i], w[i] = h[i], h[i] = t;
    for(i = 1; i < 6; i++)
    {
        for(j = i-1; j >= 0; j--)
        {
            if(w[j] < w[j+1] || (w[j] == w[j+1] && h[j] <= h[j+1]))
                break;
            t = w[j+1], w[j+1] = w[j], w[j] = t;
            t = h[j+1], h[j+1] = h[j], h[j] = t;
        }
    }
    for(i = 0; i < 6; i += 2)
        if(w[i] != w[i+1] || h[i] != h[i+1])
            return false;
    return w[0] == w[2] && h[2] == h[4] && w[4] == h[0];
}

int main()
{
    int i;
    while(scanf("%d%d", &w[0], &h[0]) != EOF)
    {
        for(i = 1; i < 6; i++)
            scanf("%d%d", &w[i], &h[i]);
        if(solve())
            printf("POSSIBLE\n");
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}

