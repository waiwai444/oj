#include <cstdio>
#include <cstring>

int n;
int init[10];

bool dfs(int *a, int steps, int inv)
{
    int i, j, k, inv2, b[10];
    if(inv == 0)
        return true;
    if(steps*3 < inv)
        return false;
    for(i = 0; i < n; ++i)
    {
        if(i > 0 && a[i-1]+1 == a[i])
            continue;
        std::memcpy(b, a, i*sizeof(int));
        for(j = i+1; j < n; ++j)
        {
            for(k = 1; k <= n-j; ++k)
            {
                if(a[i+k-1]+1 == a[i+k] || a[j+k-1]+1 == a[j+k])
                    continue;
                std::memcpy(&b[i], &a[i+k], (j-i)*sizeof(int));
                std::memcpy(&b[j], &a[i], k*sizeof(int));
                if(j+k < n)
                    std::memcpy(&b[j+k], &a[j+k], (n-j-k)*sizeof(int));
                inv2 = inv;
                if(i > 0 && b[i-1]+1 == b[i])
                    --inv2;
                if(b[j-1]+1 == b[j])
                    --inv2;
                if(b[j+k-1]+1 == b[j+k])
                    --inv2;
                if(dfs(b, steps-1, inv2))
                    return true;
            }
        }
    }
    return false;
}

int iddfs()
{
    int i, inv = 0, max = 0;
    for(i = 1; i < n; ++i)
        if(init[i-1] != init[i]-1)
            ++inv;
    for(;;)
    {
        if(dfs(init, max, inv))
            return max;
        ++max;
    }
}

int main()
{
    int i, tc = 0;
    while(std::scanf("%d", &n), n)
    {
        for(i = 0; i < n; ++i)
            std::scanf("%d", &init[i]);
        std::printf("Case %d: %d\n", ++tc, iddfs());
    }
    return 0;
}
