#include <algorithm>
#include <stdio.h>

int k;
int seq[5001];
int lsmall[5001], rlarge[5001];

bool solve()
{
    int i, j;
    for(i = 0; i < k; ++i)
    {
        lsmall[i] = 100001;
        rlarge[i] = 0;
    }
    for(i = 0; i < k; ++i)
    {
        for(j = i - 1; j >= 0; --j)
            if(seq[j] < seq[i])
            {
                lsmall[i] = seq[j];
                break;
            }
        for(j = i + 1; j < k; ++j)
            if(seq[j] > seq[i])
            {
                rlarge[i] = seq[j];
                break;
            }
    }
    for(i = 1; i < k - 2; ++i)
    {
        for(j = i + 1; j < k - 1; ++j)
        {
            if(seq[i] > seq[j] && lsmall[i] > seq[j] && rlarge[j] < seq[i] && lsmall[i] < rlarge[j])
                return true;
        }
    }
    return false;
}

int main()
{
    int i, T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &k);
        for(i = 0; i < k; ++i)
            scanf("%d", &seq[i]);
        bool ans = solve();
        if(!ans)
        {
            std::reverse(&seq[0], &seq[k]);
            ans = solve();
        }
        ans ? printf("YES\n") : printf("NO\n");
    }
    return 0;
}
