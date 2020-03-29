#include <cstdio>
#include <cstring>

#define MAXN 1000000

int n, m, k;
int seq[MAXN];
int cnt[101];

void get_seq()
{
    seq[0] = 1, seq[1] = 2, seq[2] = 3;
    for(int i = 3; i < n; i++)
    {
        int t = seq[i-1]+seq[i-2]+seq[i-3];
        while(t >= m)
            t -= m;
        seq[i] = t+1;
    }
}

int solve()
{
    int i, j, s, ans = MAXN+1;
    memset(cnt, 0, sizeof(cnt));
    s = 0;
    for(i = j = 0; j < n; j++)
    {
        if(seq[j] <= k)
        {
            if(cnt[seq[j]]++ == 0)
                ++s;
            if(s == k)
            {
                ans = j-i+1;
                while(i < j)
                {
                    if(seq[i] <= k && --cnt[seq[i]] == 0)
                        --s;
                    ++i;
                    if(s < k)
                        break;
                    --ans;
                }
                break;
            }
        }
    }
    while(ans > k && j < n-1)
    {
        if(seq[i] <= k && --cnt[seq[i]] == 0)
            --s;
        ++i;
        ++j;
        if(seq[j] <= k && cnt[seq[j]]++ == 0)
            ++s;
        if(s == k)
        {
            ans = j-i+1;
            while(i < j)
            {
                if(seq[i] <= k && --cnt[seq[i]] == 0)
                    --s;
                ++i;
                if(s < k)
                    break;
                --ans;
            }
        }
    }
    if(ans > MAXN)
        return -1;
    return ans;
}

int main()
{
    int t, c, ans;
    scanf("%d", &t);
    for(c = 1; c <= t; c++)
    {
        scanf("%d%d%d", &n, &m, &k);
        get_seq();
        ans = solve();
        printf("Case %d: ", c);
        if(ans < 0)
            printf("sequence nai\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}

