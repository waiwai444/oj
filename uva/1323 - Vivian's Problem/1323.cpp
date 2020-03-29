#include <cstdio>
#include <cstring>

using namespace std;

int mp[8] = {3, 7, 31, 127, 8191, 131071, 524287, 2147483647};
unsigned char p[8] = {2, 3, 5, 7, 13, 17, 19, 31};
unsigned char psum[256];

unsigned char mask[100];
bool flag[256];

int mc;
unsigned char mv[256];

void init()
{
    for(int i = 1; i < 256; i++)
        for(int j = 0; j < 8; j++)
            if(i&(1<<j))
                psum[i] += p[j];
}

int main()
{
    int i, j, k, n[100], ans;
    init();
    while(scanf("%d", &k) != EOF)
    {
        for(i = 0; i < k; i++)
            scanf("%d", &n[i]);
        for(i = 0; i < k; i++)
        {
            mask[i] = 0;
            for(j = 0; j < 8; j++)
            {
                if(n[i] < mp[j])
                    break;
                if(n[i]%mp[j] == 0)
                {
                    n[i] /= mp[j];
                    if(n[i]%mp[j] == 0)
                        break;
                    mask[i] |= 1<<j;
                }
            }
            if(n[i] > 1)
                mask[i] = 0;
        }
        mv[0] = 0;
        mc = 1;
        memset(flag, false, sizeof(flag));
        flag[0] = true;
        for(i = 0; i < k; i++)
        {
            if(mask[i] != 0)
            {
                for(j = 0; j < mc; j++)
                {
                    if((mv[j]&mask[i]) == 0)
                    {
                        unsigned char m = mv[j]|mask[i];
                        if(!flag[m])
                        {
                            flag[m] = true;
                            mv[mc++] = m;
                        }
                    }
                }
            }
        }
        ans = 0;
        for(i = 1; i < 256; i++)
        {
            if(flag[i] && psum[i] > ans)
                ans = psum[i];
        }
        if(ans == 0)
            printf("NO\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}

