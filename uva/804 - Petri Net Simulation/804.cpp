#include <cstdio>
#include <cstring>

int np, nt, nf;
int p[100];
int in[100][100], out[100][100], ni[100], no[100];
int in_cnt[100][100], out_cnt[100][100];

int solve()
{
    int i, j, k;
    for(i = 0; i < nf; ++i)
    {
        for(j = 0; j < nt; ++j)
        {
            for(k = 0; k < ni[j]; ++k)
                if(p[in[j][k]] < in_cnt[j][in[j][k]])
                    break;
            if(k == ni[j])
            {
                for(k = 0; k < ni[j]; ++k)
                    p[in[j][k]] -= in_cnt[j][in[j][k]];
                for(k = 0; k < no[j]; ++k)
                    p[out[j][k]] += out_cnt[j][out[j][k]];
                break;
            }
        }
        if(j == nt)
            break;
    }
    return i;
}

int main()
{
    int i, k, tc = 0;
    while(std::scanf("%d", &np), np)
    {
        for(i = 0; i < np; ++i)
            std::scanf("%d", &p[i]);
        std::scanf("%d", &nt);
        std::memset(in_cnt, 0, sizeof(in_cnt));
        std::memset(out_cnt, 0, sizeof(out_cnt));
        for(i = 0; i < nt; ++i)
        {
            ni[i] = no[i] = 0;
            std::scanf("%d", &k);
            while(k)
            {
                if(k > 0)
                {
                    if(out_cnt[i][k-1] == 0)
                        out[i][no[i]++] = k-1;
                    ++out_cnt[i][k-1];
                }
                else
                {
                    if(in_cnt[i][-k-1] == 0)
                        in[i][ni[i]++] = -k-1;
                    ++in_cnt[i][-k-1];
                }
                std::scanf("%d", &k);
            }
        }
        std::scanf("%d", &nf);
        k = solve();
        std::printf("Case %d: ", ++tc);
        if(k < nf)
            std::printf("dead after %d transitions\n", k);
        else
            std::printf("still live after %d transitions\n", nf);
        std::printf("Places with tokens:");
        for(i = 0; i < np; ++i)
            if(p[i] > 0)
                std::printf(" %d (%d)", i+1, p[i]);
        std::printf("\n\n");
    }
    return 0;
}

