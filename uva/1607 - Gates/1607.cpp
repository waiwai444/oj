#include <cstdio>

int n, m;
int input[200001][2];
int value[200001];
char ans[100001];

int compute(int x)
{
    int a, b;
    for(int i = 1; i <= m; ++i)
    {
        if(input[i][0] < 0)
            a = -input[i][0] <= x ? 1 : 0;
        else
            a = value[input[i][0]];
        if(input[i][1] < 0)
            b = -input[i][1] <= x ? 1 : 0;
        else
            b = value[input[i][1]];
        value[i] = (a&b) ? 0 : 1;
    }
    return value[m];
}

int main()
{
    int i, d, y0, yn, low, high, mid;
    scanf("%d", &d);
    while(d--)
    {
        scanf("%d%d", &n, &m);
        for(i = 1; i <= m; ++i)
            scanf("%d%d", &input[i][0], &input[i][1]);
        y0 = compute(0);
        yn = compute(n);
        if(y0 == yn)
            for(i = 0; i < n; ++i)
                ans[i] = '0';
        else
        {
            low = 1, high = n;
            while(low < high)
            {
                mid = (low+high)/2;
                if(compute(mid) == y0)
                    low = mid+1;
                else
                    high = mid;
            }
            for(i = 1; i <= n; ++i)
            {
                if(i < low)
                    ans[i-1] = '1';
                else if(i == low)
                    ans[i-1] = 'x';
                else
                    ans[i-1] = '0';
            }
        }
        ans[n] = '\0';
        puts(ans);
    }
    return 0;
}