#include <cstdio>
#include <cctype>

char str[81];

int main()
{
    int t, n;
    double ans;
    char *p, c;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s", str);
        ans = 0;
        p = str;
        while(*p)
        {
            c = *p++;
            if(isdigit(*p))
            {
                n = *p++-'0';
                if(isdigit(*p))
                    n = n*10+*p++-'0';
            }
            else
                n = 1;
            if(c == 'C')
                ans += 12.01*n;
            else if(c == 'H')
                ans += 1.008*n;
            else if(c == 'O')
                ans += 16.00*n;
            else
                ans += 14.01*n;
        }
        printf("%.3f\n", ans);
    }
    return 0;
}

