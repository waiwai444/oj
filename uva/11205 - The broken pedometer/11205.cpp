#include <stdio.h>
#include <string.h>

struct queue_elem_s
{
    int leds;
    int ones;
};

int P, N;
int symbol[100];
queue_elem_s queue[100000];
int qfront, qback;

bool check(int cur_leds)
{
    static bool flag[32768];
    memset(flag, false, sizeof(flag));
    for(int i = 0; i < N; i++)
    {
        int res = symbol[i] & cur_leds;
        if(flag[res])
            return false;
        flag[res] = true;
    }
    return true;
}

int bfs(int lb)
{
    int i, mask, cur_leds, cur_ones;
    qfront = qback = 0;
    queue[qback].leds = queue[qback].ones = 0;
    qback++;
    while(qfront != qback)
    {
        cur_leds = queue[qfront].leds;
        cur_ones = queue[qfront].ones;
        qfront++;
        if(cur_ones >= lb && check(cur_leds))
            return cur_ones;
        for(i = 0; i < P; i++)
        {
            mask = 1<<i;
            if((cur_leds & mask) != 0)
                break;
            queue[qback].leds = cur_leds | mask;
            queue[qback].ones = cur_ones+1;
            qback++;
        }
    }
    return -1;
}

int main()
{
    int tc, i, j, bit, lb, tmp;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &P, &N);
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < P; j++)
            {
                scanf("%d", &bit);
                symbol[i] = symbol[i]*2+bit;
            }
        }
        for(lb = 0, tmp = 1; tmp < N; lb++)
            tmp *= 2;
        printf("%d\n", bfs(lb));
    }
    return 0;
}