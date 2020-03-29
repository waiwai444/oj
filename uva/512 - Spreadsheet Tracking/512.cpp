#include <cstdio>
#include <vector>
#include <algorithm>

enum com_type_t { EX, DC, DR, IC, IR };

struct ex_com_t
{
    int r1, c1, r2, c2;
};

struct di_com_t
{
    int n;
    int rc[9];
};

struct com_t
{
    com_type_t type;
    union
    {
        ex_com_t ex;
        di_com_t di;
    } u;
};

std::vector<com_t> coms;

void read_command()
{
    com_t c;
    char str[5];
    scanf("%s", str);
    if(str[0] == 'E')
    {
        c.type = EX;
        scanf("%d%d%d%d", &c.u.ex.r1, &c.u.ex.c1, &c.u.ex.r2, &c.u.ex.c2);
    }
    else
    {
        if(str[0] == 'D' && str[1] == 'C')
            c.type = DC;
        else if(str[0] == 'D' && str[1] == 'R')
            c.type = DR;
        else if(str[0] == 'I' && str[1] == 'C')
            c.type = IC;
        else if(str[0] == 'I' && str[1] == 'R')
            c.type = IR;
        scanf("%d", &c.u.di.n);
        for(int i = 0; i < c.u.di.n; i++)
            scanf("%d", &c.u.di.rc[i]);
        std::sort(&c.u.di.rc[0], &c.u.di.rc[c.u.di.n]);
    }
    coms.push_back(c);
}

void solve()
{
    int i, j, r, c, r0, c0;
    scanf("%d%d", &r, &c);
    r0 = r, c0 = c;
    for(i = 0; i < coms.size(); i++)
    {
        com_t &com = coms[i];
        if(com.type == EX)
        {
            ex_com_t &ex = com.u.ex;
            if(ex.r1 == r && ex.c1 == c)
                r = ex.r2, c = ex.c2;
            else if(ex.r2 == r && ex.c2 == c)
                r = ex.r1, c = ex.c1;
        }
        else if(com.type == DC)
        {
            di_com_t &di = com.u.di;
            for(j = 0; j < di.n && di.rc[j] < c; j++);
            if(j < di.n && di.rc[j] == c)
                break;
            c -= j;
        }
        else if(com.type == DR)
        {
            di_com_t &di = com.u.di;
            for(j = 0; j < di.n && di.rc[j] < r; j++);
            if(j < di.n && di.rc[j] == r)
                break;
            r -= j;
        }
        else if(com.type == IC)
        {
            di_com_t &di = com.u.di;
            for(j = 0; j < di.n && di.rc[j] <= c; j++);
            c += j;
        }
        else if(com.type == IR)
        {
            di_com_t &di = com.u.di;
            for(j = 0; j < di.n && di.rc[j] <= r; j++);
            r += j;
        }
    }
    if(i < coms.size())
        printf("Cell data in (%d,%d) GONE\n", r0, c0);
    else
        printf("Cell data in (%d,%d) moved to (%d,%d)\n", r0, c0, r, c);
}

int main()
{
    int i, r, c, n, tc = 0;
    coms.reserve(100);
    while(scanf("%d%d", &r, &c), r)
    {
        coms.clear();
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            read_command();
        if(tc)
            printf("\n");
        printf("Spreadsheet #%d\n", ++tc);
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            solve();
    }
    return 0;
}

