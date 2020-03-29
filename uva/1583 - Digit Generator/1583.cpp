#include <cstdio>

#define MAX 100000

int ans[MAX+1];

int main()
{
    int i, s, t, n;
    for(i = 1; i < MAX; i++)
    {
        s = n = i;
        while(n)
        {
            s += n%10;
            n /= 10;
        }
        if(s <= MAX && ans[s] == 0)
            ans[s] = i;
    }
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
    return 0;
}

