#include <limits.h>
#include <stdio.h>
#include <utility>

char str1[5005];
char str2[5005];
int dp[5005][5005], res[5005][5005];

void solve()
{
    int i, j, l1, l2;
    char *p;
    std::pair<int, int> pos1[26], pos2[26];
    for(i = 0; i < 26; ++i)
        pos1[i].first = pos1[i].second = pos2[i].first = pos2[i].second = INT_MAX;
    for(i = 1, p = str1+1; *p; ++i, ++p)
    {
        *p -= 'A';
        if(pos1[*p].first == INT_MAX)
            pos1[*p].first = i;
        pos1[*p].second = i;
    }
    l1 = i-1;
    for(i = 1, p = str2+1; *p; ++i, ++p)
    {
        *p -= 'A';
        if(pos2[*p].first == INT_MAX)
            pos2[*p].first = i;
        pos2[*p].second = i;
    }
    l2 = i-1;
    for(i = 0; i <= l1; ++i)
    {
        for(j = 0; j <= l2; ++j)
        {
            if(i == 0 && j == 0)
                continue;
            int s1 = INT_MAX, s2 = INT_MAX;
            if(i > 0)
                s1 = dp[i-1][j]+res[i-1][j];
            if(j > 0)
                s2 = dp[i][j-1]+res[i][j-1];
            if(s1 < s2)
            {
                char ch = str1[i];
                dp[i][j] = s1;
                res[i][j] = res[i-1][j];
                if(pos1[ch].first < i || pos2[ch].first <= j)
                    --res[i][j];
                if(pos1[ch].second > i || (pos2[ch].first != INT_MAX && pos2[ch].second > j))
                    ++res[i][j];
            }
            else
            {
                char ch = str2[j];
                dp[i][j] = s2;
                res[i][j] = res[i][j-1];
                if(pos1[ch].first <= i || pos2[ch].first < j)
                    --res[i][j];
                if((pos1[ch].first != INT_MAX && pos1[ch].second > i) || pos2[ch].second > j)
                    ++res[i][j];
            }
        }
    }
    printf("%d\n", dp[l1][l2]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s%s", str1+1, str2+1);
        solve();
    }
    return 0;
}
