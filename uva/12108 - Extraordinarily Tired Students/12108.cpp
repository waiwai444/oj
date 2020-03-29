#include <cstdio>
#include <set>

#define HSIZE 101

int n;
int a[10], b[10], c[10];
std::set<long long> hash[HSIZE];

int main()
{
    int i, ans, s, tc = 0;
    long long d, st;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < HSIZE; i++)
            hash[i].clear();
        for(i = 0; i < n; i++)
            scanf("%d%d%d", &a[i], &b[i], &c[i]);
        for(ans = 1; ; ++ans)
        {
            s = 0, d = 1, st = 0;
            for(i = 0; i < n; i++)
            {
                if(c[i] > a[i])
                    ++s;
                st += (c[i]-1)*d;
                d *= 10;
            }
            if(s == 0)
                break;
            std::set<long long> &set = hash[st%HSIZE];
            if(set.find(st) != set.end())
                break;
            set.insert(st);
            for(i = 0; i < n; i++)
            {
                if(c[i] == a[i] && s+s <= n)
                    c[i] = 1;
                else if(c[i] == a[i]+b[i])
                    c[i] = 1;
                else
                    ++c[i];
            }
        }
        if(s != 0)
            ans = -1;
        printf("Case %d: %d\n", ++tc, ans);
    }
    return 0;
}

