#include <cstdio>

int n, t, m;
int arr[1440];
int tm, tr;

void solve()
{
    int i = 0, j = m%n;
    tr = m/n;
    if(j == 0)
        j = n;
    else
        ++tr;
    tm = 0;
    while(i < m)
    {
        if(tm > arr[j-1])
            tm += 2*t;
        else
            tm = arr[j-1]+2*t;
        i = j;
        j += n;
    }
    tm -= t;
}

int main()
{
    int i, c;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%d%d%d", &n, &t, &m);
        for(i = 0; i < m; i++)
            scanf("%d", &arr[i]);
        solve();
        printf("%d %d\n", tm, tr);
    }
    return 0;
}

