#include <cstdio>
#include <climits>

int seq[9];

const char *conf[6] = {
    "BCG", "BGC", "CBG", "CGB", "GBC", "GCB"
};

const int mov[6][6] = {
    { 1, 2, 3, 4, 6, 8 },
    { 1, 2, 3, 5, 6, 7 },
    { 0, 1, 4, 5, 6, 8 },
    { 0, 1, 3, 5, 7, 8 },
    { 0, 2, 4, 5, 6, 7 },
    { 0, 2, 3, 4, 7, 8 }
};

int main()
{
    int i, j, c, min, t;
    while(scanf("%d", &seq[0]) != EOF)
    {
        for(i = 1; i < 9; i++)
            scanf("%d", &seq[i]);
        min = INT_MAX;
        for(i = 0; i < 6; i++)
        {
            t = 0;
            for(j = 0; j < 6; j++)
                t += seq[mov[i][j]];
            if(t < min)
            {
                min = t;
                c = i;
            }
        }
        printf("%s %d\n", conf[c], min);
    }
    return 0;
}

