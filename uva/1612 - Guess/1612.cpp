#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int scores[16384][8];
int rank[16384];

int main()
{
    char str[8], *p;
    int i, j, t = 0;
    int max;

    while (scanf("%d", &n) != EOF && n)
    {
        for (i = 0; i < n; ++i)
        {
            scores[i][0] = 0;
            for (j = 1; j <= 3; ++j)
            {
                scanf("%s", str);
                int v = atoi(str) * 100;
                if (p = strchr(str, '.'))
                {
                    v += (*++p - '0') * 10;
                    if (*(p + 1))
                        v += (*(p + 1) - '0');
                }
                scores[i][j] = v;
            }
            scores[i][7] = scores[i][1] + scores[i][2] + scores[i][3];
            for (j = 1; j <= 3; ++j)
                scores[i][3 + j] = scores[i][7] - scores[i][j];
            std::sort(&scores[i][1], &scores[i][7]);
        }
        for (i = 0; i < n; ++i)
            scanf("%d", &rank[i]);

        max = scores[rank[0] - 1][7];
        for (i = 1; i < n; ++i)
        {
            for (j = 7; j >= 0; --j)
            {
                int s = scores[rank[i] - 1][j];
                if (s < max)
                {
                    max = s;
                    break;
                }
                if (s == max && rank[i] > rank[i - 1])
                    break;
            }
            if (j < 0)
                break;
        }

        printf("Case %d: ", ++t);
        if (i < n)
            puts("No solution");
        else
            printf("%d.%02d\n", max / 100, max % 100);
    }

    return 0;
}