#include <stdio.h>

int h, w;
char pic[100][101];

int main()
{
    int i, a;
    bool in;
    while(scanf("%d%d", &h, &w) != EOF)
    {
        for(i = 0; i < h; ++i)
            scanf("%s", pic[i]);
        a = 0;
        in = false;
        for(i = 0; i < h; ++i)
        {
            for(char *p = pic[i]; *p; ++p)
            {
                if(*p == '/' || *p == '\\')
                {
                    in = !in;
                    if(in)
                        ++a;
                }
                else if(in)
                    ++a;
            }
        }
        printf("%d\n", a);
    }
    return 0;
}
