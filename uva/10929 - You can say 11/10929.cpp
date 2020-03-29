#include <cstdio>

char num[1010];

int main()
{
    int i, n1, n2;
    char *p;
    while(scanf("%s", num))
    {
        if(num[0] == '0' && num[1] == 0)
            break;
        n1 = n2 = 0;
        p = num;
        while(*p)
        {
            n1 += (*p++)-'0';
            if(*p)
                n2 += (*p++)-'0';
        }
        if((n1-n2)%11 == 0)
            printf("%s is a multiple of 11.\n", num);
        else
            printf("%s is not a multiple of 11.\n", num);
    }
    return 0;
}

