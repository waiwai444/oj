#include <stdio.h>
#include <algorithm>

int n;
int p[1000002];
int s[1000002];
int left[1000002];

int solve()
{
    int i, l = -1, ceil = 1000, sum = 0;

    p[0] = p[n+1] = s[0] = s[n+1] = 1000;

    for (i = 0; i <= n; ++i)
    {
        if(l >= 0 && s[i] < ceil)
            ceil = s[i];
        if(p[i] > p[i+1])
            left[++l] = i;
        else if(p[i] < p[i+1])
        {
            int floor = p[i];
            while(l >= 0)
            {
                int w = i-left[l];
                if(p[i+1] >= ceil && p[left[l]] >= ceil)
                {
                    sum += w*(ceil-floor);
                    l = -1;
                    break;
                }
                sum += w*(std::min(p[i+1], p[left[l]])-floor);
                if(p[left[l]] > p[i+1])
                    break;
                floor = p[left[l--]];
            }
            if(l < 0)
                ceil = 1000;
        }
    }

    return sum;
}

int main()
{
    int i, Z;
    scanf("%d", &Z);
    while(Z--)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; ++i)
            scanf("%d", &p[i]);
        for(i = 1; i <= n; ++i)
            scanf("%d", &s[i]);
        printf("%d\n", solve());
    }
    return 0;
}