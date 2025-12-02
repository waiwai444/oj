#include <stdio.h>

int main()
{
    int h1, m1, h2, m2, mc, p;
    puts("Program 3 by team X");
    puts("Initial time  Final time  Passes");
    while(scanf("%d%d%d%d", &h1, &m1, &h2, &m2) != EOF)
    {
        p = 0;
        if(h1 == h2 && m1 < m2)
        {
            if(h1 < 11)
            {
                mc = 60*h1/11;
                if(m1 <= mc && m2 > mc)
                    ++p;
            }
        }
        else
        {
            if(h1 < 11)
            {
                mc = 60*h1/11;
                if(m1 <= mc)
                    ++p;
            }
            if(h2 < 11)
            {
                mc = 60*h2/11;
                if(m2 > mc)
                    ++p;
            }
            else if(h2 == 12)
                ++p;  // 12:00
            if(h2 > h1+1)
            {
                if(h2 != 12)
                    p += h2-h1-1;
                else
                    p += h2-h1-2;
            }
            else if(h2 <= h1)
            {
                if(h1 == 11 || (h1 == 12 && h2 <= 11))
                    p += h2+12-h1-1;
                else
                    p += h2+12-h1-2;
            }
        }
        printf("       %02d:%02d       %02d:%02d      %2d\n", h1, m1, h2, m2, p);
    }
    puts("End of program 3 by team X");
    return 0;
}
