#include <stdio.h>

int n;
int a[100001];

int main()
{
    int i;
    long long sum;
    while(scanf("%d", &n) != EOF)
    {
        sum = 0;
        for(i = 0; i < n; ++i)
        {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        if(sum&1)
        {
            printf("No\n");
        }
        else
        {
            sum /= 2;
            for(i = n-1; i >= 0; --i)
            {
                if(a[i] <= sum)
                {
                    sum -= a[i];
                    a[i] = 1;
                }
                else
                {
                    a[i] = -1;
                }
            }
            printf("Yes\n%d", a[0]);
            for(i = 1; i < n; ++i)
                printf(" %d", a[i]);
            printf("\n");
        }
    }
    return 0;
}
