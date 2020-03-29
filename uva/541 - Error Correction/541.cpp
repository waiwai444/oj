#include <cstdio>

int n;
int mat[100][100];
int col_check[100];

int main()
{
    int i, j, r, c, s;
    while(std::scanf("%d", &n) != EOF && n)
    {
        r = c = -1;
        for(i = 0; i < n; ++i)
            col_check[i] = 0;
        for(i = 0; i < n; ++i)
        {
            s = 0;
            for(j = 0; j < n; ++j)
            {
                std::scanf("%d", &mat[i][j]);
                s ^= mat[i][j];
                col_check[j] ^= mat[i][j];
            }
            if(s)
            {
                if(r == -1)
                    r = i;
                else
                    r = -2;
            }
        }
        if(r == -2)
            std::printf("Corrupt\n");
        else
        {
            for(i = 0; i < n; ++i)
            {
                if(col_check[i])
                {
                    if(c == -1)
                        c = i;
                    else
                        break;
                }
            }
            if(i < n)
                std::printf("Corrupt\n");
            else if(r == -1 && c == -1)
                std::printf("OK\n");
            else
                std::printf("Change bit (%d,%d)\n", r+1, c+1);
        }
    }
    return 0;
}
