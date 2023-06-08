#include <limits.h>
#include <map>
#include <stdio.h>

int n;
int seq[200000];
int left[200000];
int right[200000];

bool has_boring(int l, int r)
{
    int i, j;
    if(l >= r)
        return false;
    for(i = l, j = r; i <= j; ++i, --j)
    {
        if(left[i] < l && right[i] > r)
            return has_boring(l, i-1) ? true : has_boring(i+1, r);
        if(left[j] < l && right[j] > r)
            return has_boring(l, j-1) ? true : has_boring(j+1, r);
    }

    return true;
}

bool is_boring()
{
    int i, j;
    std::map<int, int> mp;
    std::map<int, int>::iterator it;
    for(i = 0; i < n; ++i)
    {
        right[i] = INT_MAX;
        it = mp.find(seq[i]);
        if(it == mp.end())
        {
            left[i] = -1;
            mp[seq[i]] = i;
        }
        else
        {
            left[i] = it->second;
            right[it->second] = i;
            it->second = i;
        }
    }
    return has_boring(0, n-1);
}

int main()
{
    int t, i;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
            scanf("%d", &seq[i]);
        puts(is_boring() ? "boring" : "non-boring");
    }
    return 0;
}