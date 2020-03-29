#include <cstdio>

#define MAXL 100000

char str[MAXL+5];
long h[MAXL+1], e[MAXL+1];
long len, nh, ne;

int main()
{
    long i;
    char *p;
    while(std::fgets(str, sizeof(str), stdin))
    {
        p = str, len = ne = 0;
        h[0] = 0, nh = 1;
        while(*p)
        {
            if(*p == '\n' || *p == '\r')
            {
                *p = '\0';
                break;
            }
            if(*p == '[')
            {
                *p = '\0';
                h[nh++] = len+1;
            }
            else if(*p == ']')
            {
                *p = '\0';
                e[ne++] = len+1;
            }
            ++len, ++p;
        }
        for(i = nh-1; i >= 0; --i)
            std::fputs(&str[h[i]], stdout);
        for(i = 0; i < ne; ++i)
            std::fputs(&str[e[i]], stdout);
        std::putchar('\n');
    }
    return 0;
}

