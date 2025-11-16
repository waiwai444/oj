#include <algorithm>
#include <stdio.h>

int a, b, m, n;
int d[510][510];

int rb[510];

bool check(int *area, int width, int height)
{
    int a1 = std::min(width, a)*std::min(height, b);
    int a2 = std::min(width, b)*std::min(height, a);
    *area = std::max(*area, std::max(a1, a2));
    return *area == a*b;
}

int max_bottom(int x, int y)
{
    int i, j, k, ul, dl;
    int s = 0, cd = d[x][y];
    for(j = y+1; j < n && d[x][j] >= cd; ++j);
    rb[x] = j-1;
    if(check(&s, j-y, 1))
        return s;
    for(i = x+1; i < m && d[i][y] >= cd; ++i)
    {
        for(j = y+1; j <= rb[i-1] && d[i][j] >= cd; ++j);
        rb[i] = j-1;
        if(check(&s, j-y, i-x+1))
            return s;
    }
    ul = i;
    for(i = x-1; i >= 0 && d[i][y] >= cd; --i)
    {
        for(j = y+1; j <= rb[i+1] && d[i][j] >= cd; ++j)
        rb[i] = j-1;
        if(check(&s, j-y, x-i+1))
            return s;
    }
    dl = i;
    for(j = y-1; j >= 0 && d[x][j] >= cd; --j)
    {
        for(i = x; i > dl+1 && d[i-1][j] >= cd; --i);
        dl = i-1;
        for(k = x; k < ul-1 && d[k+1][j] >= cd; ++k);
        ul = k+1;
        while(i < k)
        {
            if(check(&s, std::min(rb[i], rb[k])-j+1, k-i+1))
                return s;
            if((k == x || rb[i] <= rb[k]) && i < x)
                ++i;
            if((i == x || rb[i] >= rb[k]) && k > x)
                --k;
        }
        if(check(&s, rb[x]-j+1, 1))
            return s;
    }
    return s;
}

int solve()
{
    int i, j, s, h;
    int ans = 0;
    for(i = 0; i < m; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            s = max_bottom(i, j);
            h = (s*d[i][j]-1)/(m*n-s)+d[i][j];
            ans = std::max(ans, s*h);
        }
    }
    return ans;
}

int main()
{
    int i, j;
    while(scanf("%d%d%d%d", &a, &b, &m, &n) != EOF)
    {
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                scanf("%d", &d[i][j]);
        printf("%d\n", solve());
    }
    return 0;
}
