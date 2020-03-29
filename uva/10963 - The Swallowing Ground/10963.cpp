#include <cstdio>

int main()
{
    int i, tc, w, u, v, d;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &w);
        bool ans = true;
        if(w > 0)
        {
            scanf("%d%d", &u, &v);
            d = u-v;
            for(i = 1; i < w; i++)
            {
                scanf("%d%d", &u, &v);
                if(u-v != d)
                    ans = false;
            }
        }
        if(ans)
            printf("yes\n");
        else
            printf("no\n");
        if(tc)
            printf("\n");
    }
    return 0;
}

