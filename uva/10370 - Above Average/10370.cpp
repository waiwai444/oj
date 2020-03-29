#include <cstdio>

int n, num[1000];

int main()
{
    int c, i, avg, cnt;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%d", &n);
        avg = 0;
        for(i = 0; i < n; i++)
        {
            scanf("%d", &num[i]);
            avg += num[i];
        }
        avg /= n;
        cnt = 0;
        for(i = 0; i < n; i++)
            if(num[i] > avg)
                ++cnt;
        printf("%.3f%%\n", (double)cnt/n*100+1e-9);
    }
    return 0;
}

