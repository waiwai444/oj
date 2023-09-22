#include <stdio.h>
#include <utility>

int n;
int val[10001];
int pos[10001];
int nsteps;
std::pair<int, int> steps[531441];

inline void swap(int left, int right)
{
    int mid = (left+right)/2+1;
    for(int i = left; i < mid; ++i)
    {
        std::swap(val[i], val[mid+i-left]);
        std::swap(pos[val[i]], pos[val[mid+i-left]]);
    }
}

void solve()
{
    int i;
    nsteps = 0;
    for(i = 1; i <= n; ++i)
    {
        if(val[i] == i)
            continue;
        if(pos[i]+pos[i]-i-1 >= n)
        {
            steps[nsteps++] = std::make_pair(n-(n-i+1)/2*2+1, n);
            swap(n-(n-i+1)/2*2+1, n);
        }
        if(val[i] != i)
        {
            steps[nsteps++] = std::make_pair(i, pos[i]+pos[i]-i-1);
            swap(i, pos[i]+pos[i]-i-1);
        }
    }

    printf("%d\n", nsteps);
    for(i = 0; i < nsteps; ++i)
        printf("%d %d\n", steps[i].first, steps[i].second);
}

int main()
{
    int i, T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d", &val[i]);
            pos[val[i]] = i;
        }
        solve();
    }
    return 0;
}
