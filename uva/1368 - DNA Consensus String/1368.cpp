#include <cstdio>
#include <cstring>

int n;
char dna[1001];
int cnt[1000][4];

inline int get_idx(char c)
{
    if(c == 'A') return 0;
    if(c == 'C') return 1;
    if(c == 'G') return 2;
    return 3;
}

inline char get_ch(int i)
{
    if(i == 0) return 'A';
    if(i == 1) return 'C';
    if(i == 2) return 'G';
    return 'T';
}

int main()
{
    int i, j, t, m, d;
    scanf("%d", &t);
    while(t--)
    {
        memset(cnt, 0, sizeof(cnt));
        scanf("%d%d", &m, &n);
        for(i = 0; i < m; i++)
        {
            scanf("%s", dna);
            for(j = 0; j < n; j++)
                ++cnt[j][get_idx(dna[j])];
        }
        d = 0;
        for(i = 0; i < n; i++)
        {
            j = 0;
            if(cnt[i][1] > cnt[i][j]) j = 1;
            if(cnt[i][2] > cnt[i][j]) j = 2;
            if(cnt[i][3] > cnt[i][j]) j = 3;
            dna[i] = get_ch(j);
            d += m-cnt[i][j];
        }
        printf("%s\n%d\n", dna, d);
    }
    return 0;
}

