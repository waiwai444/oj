#include <cstdio>
#include <cstring>

int n, d;
char dec[3100];
int f[3000];
int inte, s;

int main()
{
    int i, r;
    while(scanf("%d%d", &n, &d) != EOF)
    {
        s = 0;
        memset(f, -1, sizeof(f));
        inte = n/d;
        r = n%d;
        for(; f[r] < 0; ++s)
        {
            f[r] = s;
            r *= 10;
            dec[s] = r/d+'0';
            r %= d;
        }
        printf("%d/%d = %d.", n, d, inte);
        for(i = 0; i < s && i < 50; i++)
        {
            if(f[r] == i)
                putchar('(');
            putchar(dec[i]);
        }
        if(i < s)
            printf("...");
        if(f[r] <= s)
            putchar(')');
        printf("\n   %d = number of digits in repeating cycle\n\n", s-f[r]);
    }
    return 0;
}

