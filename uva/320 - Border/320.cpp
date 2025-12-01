#include <stdio.h>
#include <string.h>

char bm[32][33];
char mov[2000];

int main()
{
    int c, tc, x, y, i;
    scanf("%d", &tc);
    for(c = 1; c <= tc; ++c)
    {
        scanf("%d%d%s", &x, &y, mov);
        for(i = 0; i < 32; ++i)
            memset(bm[i], '.', 32);
        for(char *p = mov; *p != '.'; ++p)
        {
            if(*p == 'W')
            {
                --x;
                bm[y][x] = 'X';
            }
            else if(*p == 'E')
            {
                bm[y-1][x] = 'X';
                ++x;
            }
            else if(*p == 'N')
            {
                bm[y][x] = 'X';
                ++y;
            }
            else
            {
                --y;
                bm[y][x-1] = 'X';
            }
        }
        printf("Bitmap #%d\n", c);
        for(i = 31; i >= 0; --i)
            puts(bm[i]);
        putchar('\n');
    }
    return 0;
}
