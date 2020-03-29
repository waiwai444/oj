#include <cstdio>

int height[10001];

int main()
{
    int i, l, r, h, maxr = 0;
    while(scanf("%d%d%d", &l, &h, &r) != EOF)
    {
        for(i = l+1; i <= r; i++)
            if(h > height[i])
                height[i] = h;
        if(r > maxr)
            maxr = r;
    }
    for(i = 1; i <= maxr; i++)
        if(height[i] != height[i-1])
            printf("%d %d ", i-1, height[i]);
    printf("%d 0\n", maxr);
    return 0;
}

