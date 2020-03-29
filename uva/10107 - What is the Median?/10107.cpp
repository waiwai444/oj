#include <cstdio>
#include <cstring>

#define MAXN 100000

int num[MAXN], cnt, mid;
int first, last, next[MAXN], prev[MAXN];

int main()
{
    int i;
    bool after;
    memset(next, -1, sizeof(next));
    memset(prev, -1, sizeof(prev));
    first = last = -1;
    while(scanf("%d", &num[cnt]) != EOF)
    {
        if(first == -1)
        {
            first = last = 0;
            printf("%d\n", num[mid = 0]);
        }
        else
        {
            after = false;
            for(i = first; i != -1; i = next[i])
            {
                if(num[i] <= num[cnt])
                    break;
                if(i == mid)
                    after = true;
            }
            if(i == first)
            {
                next[cnt] = first;
                prev[first] = cnt;
                first = cnt;
            }
            else if(i != -1)
            {
                next[cnt] = i;
                prev[cnt] = prev[i];
                prev[i] = cnt;
                next[prev[cnt]] = cnt;
            }
            else
            {
                next[last] = cnt;
                prev[cnt] = last;
                last = cnt;
            }
            if(after)
            {
                if(cnt&1)
                    printf("%d\n", (num[mid]+num[next[mid]])/2);
                else
                {
                    mid = next[mid];
                    printf("%d\n", num[mid]);
                }
            }
            else
            {
                if(cnt&1)
                {
                    mid = prev[mid];
                    printf("%d\n", (num[mid]+num[next[mid]])/2);
                }
                else
                    printf("%d\n", num[mid]);
            }
        }
        ++cnt;
    }
    return 0;
}

