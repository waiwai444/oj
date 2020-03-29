#include <cstdio>
#include <cctype>

char code[512];
int n;
long long num[2][50];

int read_int(char *str, char **next)
{
    int r = 0, sgn = 1;
    if(*str == '-')
        sgn = -1, ++str;
    while(*str && isdigit(*str))
        r = r*10+*str++-'0';
    *next = str;
    return sgn*r;
}

void generate(char *p, int t)
{
    int i;
    int m = read_int(p+1, &p);
    char op = *p++;
    if(op == '+' || op == '*')
    {
        generate(p, 1-t);
        if(op == '+')
        {
            num[t][0] = m;
            for(i = 1; i < n; i++)
                num[t][i] = num[t][i-1]+num[1-t][i-1];
        }
        else
        {
            num[t][0] = m*num[1-t][0];
            for(i = 1; i < n; i++)
                num[t][i] = num[t][i-1]*num[1-t][i];
        }
    }
    else
    {
        for(i = 0; i < n; i++)
            num[t][i] = m;
    }
}

int main()
{
    while(scanf("%s%d", code, &n) != EOF)
    {
        generate(code, 0);
        printf("%lld", num[0][0]);
        for(int i = 1; i < n; i++)
            printf(" %lld", num[0][i]);
        printf("\n");
    }
    return 0;
}

