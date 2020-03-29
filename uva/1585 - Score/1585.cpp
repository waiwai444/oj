#include <cstdio>
#include <cstring>

int main()
{
    int i, c, t, len, s;
    char str[80];
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s", str);
        len = strlen(str);
        s = c = 0;
        for(i = 0; i < len; i++)
        {
            if(str[i] == 'O')
                s += ++c;
            else
                c = 0;
        }
        printf("%d\n", s);
    }
    return 0;
}

