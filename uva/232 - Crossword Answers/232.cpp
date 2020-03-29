#include <cstdio>
#include <cstring>

int r, c;
char grid[10][11];
int no[10][10];

int main()
{
    int i, j, k, tc = 0, n;
    while(scanf("%d%d", &r, &c), r)
    {
        for(i = 0; i < r; i++)
            scanf("%s", grid[i]);
        n = 0;
        memset(no, 0, sizeof(no));
        for(j = 0; j < c; j++)
            if(grid[0][j] != '*')
                no[0][j] = ++n;
        for(i = 1; i < r; i++)
        {
            if(grid[i][0] != '*')
                no[i][0] = ++n;
            for(j = 1; j < c; j++)
                if(grid[i][j] != '*' && (grid[i][j-1] == '*' || grid[i-1][j] == '*'))
                    no[i][j] = ++n;
        }
        if(tc)
            putchar('\n');
        printf("puzzle #%d:\nAcross\n", ++tc);
        for(i = 0; i < r; i++)
            for(j = 0; j < c; j++)
                if(no[i][j] > 0 && (j == 0 || grid[i][j-1] == '*'))
                {
                    printf("%3d.", no[i][j]);
                    for(k = j; k < c && grid[i][k] != '*'; k++)
                        putchar(grid[i][k]);
                    putchar('\n');
                }
        printf("Down\n");
        for(i = 0; i < r; i++)
            for(j = 0; j < c; j++)
                if(no[i][j] > 0 && (i == 0 || grid[i-1][j] == '*'))
                {
                    printf("%3d.", no[i][j]);
                    for(k = i; k < r && grid[k][j] != '*'; k++)
                        putchar(grid[k][j]);
                    putchar('\n');
                }
    }
    return 0;
}

