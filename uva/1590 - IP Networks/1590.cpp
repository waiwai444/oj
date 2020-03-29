#include <cstdio>

int main()
{
    int i, j, k, m;
    int a[4], b[4], mask[4];
    while(scanf("%d", &m) != EOF)
    {
        for(i = 0; i < 4; i++)
            mask[i] = 255;
        k = 3;
        scanf("%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
        for(i = 1; i < m; i++)
        {
            scanf("%d.%d.%d.%d", &b[0], &b[1], &b[2], &b[3]);
            for(j = 0; j <= k; j++)
            {
                if((mask[j]&a[j]) != (mask[j]&b[j]))
                {
                    while((mask[j]&a[j]) != (mask[j]&b[j]))
                        mask[j] = (mask[j]<<1)&0xff;
                    k = mask[j] ? j : j-1;
                    break;
                }
            }
        }
        for(i = k+1; i < 4; i++)
            mask[i] = 0;
        printf("%d.%d.%d.%d\n", a[0]&mask[0], a[1]&mask[1], a[2]&mask[2], a[3]&mask[3]);
        printf("%d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
    }
    return 0;
}

