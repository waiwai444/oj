#include <cstdio>
#include <cstring>

#define MAXN 300000
#define MAXV 20000000

int n;
int ndesc[MAXN];
int fst_ch[MAXN], lst_ch[MAXN];
int pre[MAXV], post[MAXV];

struct elem_t
{
    int u;
    int c;
} stack[MAXN];
int top;

void prep()
{
    int i, j, k;
    memset(fst_ch, -1, sizeof(fst_ch));
    memset(lst_ch, -1, sizeof(lst_ch));
    for(i = 0, j = 1; i < n; i++)
    {
        if(ndesc[i] > 0)
        {
            fst_ch[i] = j, lst_ch[i] = j+ndesc[i]-1;
            j += ndesc[i];
        }
    }

    j = k = 0;
    stack[0].u = 0, stack[0].c = fst_ch[0];
    top = 1;
    while(top)
    {
        elem_t &e = stack[top-1];
        if(e.c == -1)
        {
            pre[e.u] = j++;
            post[e.u] = k++;
            --top;
        }
        else if(e.c <= lst_ch[e.u])
        {
            if(e.c == fst_ch[e.u])
                pre[e.u] = j++;
            if(e.c >= n)
            {
                while(e.c <= lst_ch[e.u])
                {
                    pre[e.c] = j++;
                    post[e.c] = k++;
                    ++e.c;
                }
            }
            else
            {
                stack[top].u = e.c;
                stack[top++].c = fst_ch[e.c];
                ++e.c;
            }
        }
        else if(e.c > lst_ch[e.u])
        {
            post[e.u] = k++;
            --top;
        }
    }
}

bool is_descendant(int a, int b)
{
    if(a >= n || a >= b || ndesc[a] == 0)
        return false;
    return pre[b] > pre[a] && post[b] < post[a];
}

int main()
{
    int i, c, tc, m, a, b;
    scanf("%d", &tc);
    for(c = 1; c <= tc; ++c)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &ndesc[i]);

        prep();

        scanf("%d", &m);
        printf("Case %d:\n", c);
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &a, &b);
            if(is_descendant(a, b))
                printf("Yes\n");
            else
                printf("No\n");
        }
        if(c < tc)
            printf("\n");
    }
    return 0;
}

