#include <cstdio>
#include <vector>
#include <algorithm>

int n;
char sq[64][65];
std::vector<long> pn;

void get_path_number(int r, int c, int s, long p, long b)
{
    int i, j;
    if(s == 1)
    {
        if(sq[r][c] == '1')
            pn.push_back(p);
        return;
    }
    for(i = r; i < r+s; ++i)
    {
        for(j = c; j < c+s; ++j)
        {
            if(sq[i][j] != '1')
            {
                get_path_number(r, c, s/2, b+p, b*5);
                get_path_number(r, c+s/2, s/2, 2*b+p, b*5);
                get_path_number(r+s/2, c, s/2, 3*b+p, b*5);
                get_path_number(r+s/2, c+s/2, s/2, 4*b+p, b*5);
                return;
            }
        }
    }
    pn.push_back(p);
}

void handle_01_repr()
{
    int i;
    for(i = 0; i < n; ++i)
        std::scanf("%s", sq[i]);
    pn.clear();
    get_path_number(0, 0, n, 0, 1);
    std::sort(pn.begin(), pn.end());
    if(pn.size() > 0)
    {
        std::printf("%ld", pn[0]);
        for(i = 1; i < (long)pn.size(); ++i)
        {
            if(i%12 == 0)
                std::printf("\n%ld", pn[i]);
            else
                std::printf(" %ld", pn[i]);
        }
        std::putchar('\n');
    }
    std::printf("Total number of black nodes = %ld\n", (long)pn.size());
}

void fill_ascii(int r, int c, int s, long p)
{
    int i, j, d;
    if(p == 0)
    {
        for(i = r; i < r+s; ++i)
            for(j = c; j < c+s; ++j)
                sq[i][j] = '*';
        return;
    }
    d = p%5;
    p /= 5;
    if(d == 1)
        fill_ascii(r, c, s/2, p);
    else if(d == 2)
        fill_ascii(r, c+s/2, s/2, p);
    else if(d == 3)
        fill_ascii(r+s/2, c, s/2, p);
    else if(d == 4)
        fill_ascii(r+s/2, c+s/2, s/2, p);
}

void handle_path_repr()
{
    int i, j;
    long p;
    pn.clear();
    for(;;)
    {
        std::scanf("%ld", &p);
        if(p == -1)
            break;
        pn.push_back(p);
    }
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
            sq[i][j] = '.';
        sq[i][n] = '\0';
    }
    for(i = 0; i < (long)pn.size(); ++i)
        fill_ascii(0, 0, n, pn[i]);
    for(i = 0; i < n; ++i)
        std::printf("%s\n", sq[i]);
}

int main()
{
    int tc = 0;
    pn.reserve(2048);
    while(std::scanf("%d", &n), n)
    {
        if(tc > 0)
            std::putchar('\n');
        std::printf("Image %d\n", ++tc);
        if(n > 0) 
            handle_01_repr();
        else
        {
            n = -n;
            handle_path_repr();
        }
    }
    return 0;
}

