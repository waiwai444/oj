#include <cstdio>

int sqn_cnt[100001];

int main()
{
    int i, a, b;
    for(i = 1; i*i <= 100000; ++i)
        sqn_cnt[i*i] = 1;
    for(i = 1; i <= 100000; ++i)
    {
        if(sqn_cnt[i] == 1)
            sqn_cnt[i] += sqn_cnt[i-1];
        else
            sqn_cnt[i] = sqn_cnt[i-1];
    }
    while(std::scanf("%d%d", &a, &b) != EOF)
    {
        if(a == 0 && b == 0)
            break;
        std::printf("%d\n", sqn_cnt[b]-sqn_cnt[a-1]);
    }
    return 0;
}
