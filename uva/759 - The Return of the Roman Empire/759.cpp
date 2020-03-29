#include <cstdio>

#define NA '-'

char rom[64];

int digit(char **ptr, char unit, char half, char next)
{
    if(**ptr == unit && *(*ptr+1) == half)
    {
        *ptr += 2;
        return 4;
    }
    if(**ptr == unit && *(*ptr+1) == next)
    {
        *ptr += 2;
        return 9;
    }
    int r = 0, c = 0;
    if(**ptr == half)
    {
        ++*ptr;
        r = 5;
    }
    while(**ptr == unit)
    {
        ++c;
        ++*ptr;
        if(c == 3)
            break;
    }
    return r+c;
}

int transform()
{
    int r = 0, d = 3;
    char *p = rom;
    while(*p)
    {
        if(*p == 'M')
        {
            if(d < 3)
                return -1;
            r += 1000*digit(&p, 'M', NA, NA);
            d = 2;
        }
        else if(*p == 'C' || *p == 'D')
        {
            if(d < 2)
                return -1;
            r += 100*digit(&p, 'C', 'D', 'M');
            d = 1;
        }
        else if(*p == 'X' || *p == 'L')
        {
            if(d < 1)
                return -1;
            r += 10*digit(&p, 'X', 'L', 'C');
            d = 0;
        }
        else if(*p == 'I' || *p == 'V')
        {
            if(d < 0)
                return -1;
            r += digit(&p, 'I', 'V', 'X');
            d = -1;
        }
    }
    return r;
}

int main()
{
    int ans;
    while(scanf("%s", rom) != EOF)
    {
        ans = transform();
        if(ans >= 0)
            printf("%d\n", ans);
        else
            puts("This is not a valid number");
    }
    return 0;
}

