#include <algorithm>
#include <math.h>
#include <stdio.h>

int w, h;
char img[110][110];

struct circle_t
{
    int r, x, y;
} circle[5];
int nc;

bool cmp_circle(const circle_t &c1, const circle_t &c2)
{
    if(c1.r < c2.r)
        return true;
    if(c1.r > c2.r)
        return false;
    if(c1.x < c2.x)
        return true;
    if(c1.x > c2.x)
        return false;
    if(c1.y < c2.y)
        return true;
    return false;
}

bool precheck(int cx, int cy, int r)
{
    return img[cy][cx-r]+img[cy-1][cx-r]+img[cy+1][cx-r]
        +img[cy][cx+r]+img[cy-1][cx+r]+img[cy+1][cx+r]
        +img[cy-r][cx]+img[cy-r][cx-1]+img[cy-r][cx+1]
        +img[cy+r][cx]+img[cy+r][cx-1]+img[cy+r][cx+1] > 4;
}

bool check(int cx, int cy, int r)
{
    int i, j, c1, c2;
    double x;
    c1 = 4;
    c2 = img[cy][cx-r]+img[cy][cx+r]+img[cy-r][cx]+img[cy+r][cx];
    j = cx-r;
    for(i = cy-1; i > cy-r; --i)
    {
        x = cx-sqrt(r*r-(0.5+cy-i)*(0.5+cy-i));
        c1 += 4;
        c2 += img[i][j]+img[i][cx+cx-j]+img[cy+cy-i][j]+img[cy+cy-i][cx+cx-j];
        while(x > j+0.5)
        {
            ++j;
            c1 += 4;
            c2 += img[i][j]+img[i][cx+cx-j]+img[cy+cy-i][j]+img[cy+cy-i][cx+cx-j];
        }
        if(x == j+0.5)
            ++j;
    }
    while(j < cx)
    {
        c1 += 4;
        c2 += img[i][j]+img[i][cx+cx-j]+img[cy+cy-i][j]+img[cy+cy-i][cx+cx-j];
        ++j;
    }
    return (double)c2/c1 >= 0.95;
}

void solve()
{
    int i, j, k;
    nc = 0;
    for(i = 5; i < h-5; ++i)
    {
        for(j = 5; j < w-5; ++j)
        {
            for(k = 5; ; ++k)
            {
                if(i-k < 0 || i+k >= h || j-k < 0 || j+k >= w)
                    break;
                if(!precheck(j, i, k))
                    continue;
                if(check(j, i, k))
                {
                    circle[nc].r = k;
                    circle[nc].x = j;
                    circle[nc].y = i;
                    ++nc;
                    if(nc >= 5)
                    {
                        i = h, j = w;
                        break;
                    }
                }
            }
        }
    }
    std::sort(circle, circle+nc, cmp_circle);
}

int main()
{
    int i, j, c, T;
    scanf("%d", &T);
    for(c = 1; c <= T; ++c)
    {
        scanf("%d%d", &w, &h);
        for(i = 0; i < h; ++i)
        {
            scanf("%s", img[i]);
            for(j = 0; j < w; ++j)
                img[i][j] -= '0';
        }
        solve();
        printf("Case %d: %d", c, nc);
        for(i = 0; i < nc; ++i)
            printf(" (%d,%d,%d)", circle[i].r, circle[i].x, circle[i].y);
        putchar('\n');
    }
    return 0;
}
