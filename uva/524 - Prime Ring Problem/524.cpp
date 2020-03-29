#include <stdio.h>

int n;
int ring[16];
bool used[17];

char is_prime[32] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};

void print_cycle()
{
    printf("1");
    for(int i = 1; i < n; i++)
        printf(" %d", ring[i]);
    printf("\n");
}

void arrange(int cur)
{
    int i;
    if(cur == n)
    {
        if(is_prime[ring[cur-1]+ring[0]])
            print_cycle();
        return;
    }
    for(i = 2; i <= n; i++)
    {
        if(!used[i] && is_prime[i+ring[cur-1]])
        {
            ring[cur] = i;
            used[i] = true;
            arrange(cur+1);
            used[i] = false;
        }
    }
}

int main()
{
    int tc = 0;
    ring[0] = 1;
    used[1] = true;
    while(scanf("%d", &n) != EOF)
    {
        if(tc > 0)
            printf("\n");
        printf("Case %d:\n", ++tc);
        arrange(1);
    }
    return 0;
}
