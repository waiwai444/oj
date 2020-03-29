#include <cstdio>

int d, s, b;
char e;
char arr[6][64*100+1];

int main()
{
    int i, j, k, l, pb, tc = 0;
    char tmp[2], p, r;
    bool x;
    while(scanf("%d%d%d", &d, &s, &b), d)
    {
        scanf("%s", tmp);
        e = (tmp[0] == 'E' ? 0 : 1);
        l = s*b;
        for(i = 0; i < d; i++)
        {
            scanf("%s", arr[i]);
            for(j = 0; j < l; j++)
                if(arr[i][j] == '0' || arr[i][j] == '1')
                    arr[i][j] -= '0';
        }
        for(i = 0; i < l; i++)
        {
            p = e;
            x = false;
            for(j = 0; j < d; j++)
            {
                if(arr[j][i] != 'x')
                    p ^= arr[j][i];
                else
                {
                    if(x)
                        break;
                    x = true;
                    k = j;
                }
            }
            if(j < d)
                break;
            if(!x && p)
                break;
            if(x)
                arr[k][i] = p;
        }
        ++tc;
        if(i < l)
            printf("Disk set %d is invalid.\n", tc);
        else
        {
            printf("Disk set %d is valid, contents are: ", tc);
            pb = 0;
            r = p = 0;
            for(i = 0; i < b; i++)
            {
                for(j = 0; j < d; j++)
                {
                    if(j == pb)
                        continue;
                    for(k = i*s; k < i*s+s; k++)
                    {
                        r = (r<<1)+arr[j][k];
                        if(++p == 4)
                        {
                            printf("%X", r);
                            r = p = 0;
                        }
                    }
                }
                if(++pb == d)
                    pb = 0;
            }
            if(p)
            {
                while(++p <= 4)
                    r <<= 1;
                printf("%X", r);
            }
            printf("\n");
        }
    }
    return 0;
}

