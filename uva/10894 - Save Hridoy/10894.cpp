#include <cstdio>

const char hban[5][62] = {
    "*****..***..*...*.*****...*...*.*****.*****.***...*****.*...*",
    "*.....*...*.*...*.*.......*...*.*...*...*...*..*..*...*..*.*.",
    "*****.*****.*...*.***.....*****.*****...*...*...*.*...*...*..",
    "....*.*...*..*.*..*.......*...*.*.*.....*...*..*..*...*...*..",
    "*****.*...*...*...*****...*...*.*..**.*****.***...*****...*.."
};
char vban[61][6];

void init()
{
    int i, j, k;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 5; j++)
            for(k = 0; k < 5; k++)
                vban[i*6+j][k] = hban[j][i*6+k];
        for(k = 0; k < 5; k++)
            vban[i*6+5][k] = '.';
    }
    for(k = 0; k < 5; k++)
        vban[24][k] = '.';
    for(i = 0; i < 6; i++)
    {
        for(k = 0; k < 5; k++)
            vban[25+i*6][k] = '.';
        for(j = 0; j < 5; j++)
            for(k = 0; k < 5; k++)
                vban[26+i*6+j][k] = hban[j][26+i*6+k];
    }
}

char line[3100];

void print_banner(int n)
{
    char *ban, *out;
    int row, col;
    int i, j, k;

    if(n > 0)
    {
        ban = (char *)hban;
        row = 5, col = 61;
    }
    else
    {
        n = -n;
        ban = (char *)vban;
        row = 61, col = 5;
    }

    for(i = 0; i < row; i++)
    {
        out = line;
        for(j = 0; j < col; j++)
        {
            for(k = 0; k < n; k++)
                *out++ = *(ban+i*(col+1)+j);
        }
        *out = 0;
        for(k = 0; k < n; k++)
            printf("%s\n", line);
    }

    printf("\n\n");
}

int main()
{
    int n;
    init();
    while(scanf("%d", &n), n)
        print_banner(n);
    return 0;
}

