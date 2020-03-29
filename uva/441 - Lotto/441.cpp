#include <cstdio>

int k, S[13];

void choose(int p, int q, int st[])
{
    int i;
    if(q == 6)
    {
        std::printf("%d", st[0]);
        for(i = 1; i < 6; ++i)
            std::printf(" %d", st[i]);
        std::putchar('\n');
        return;
    }
    for(i = p; k-i >= 6-q; ++i)
    {
        st[q] = S[i];
        choose(i+1, q+1, st);
    }
}

int main()
{
    int i, st[6];
    bool first = true;
    while(std::scanf("%d", &k) != EOF && k)
    {
        for(i = 0; i < k; ++i)
            std::scanf("%d", &S[i]);
        if(!first)
            std::putchar('\n');
        else
            first = false;
        choose(0, 0, st);
    }
    return 0;
}
