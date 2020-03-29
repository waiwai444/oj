#include <stdio.h>

int N, H;

void output(int cur_pos, char cur_str[])
{
    for(int i = cur_pos+1; i < N; i++)
        cur_str[i] = '0';
    cur_str[N] = '\0';
    printf("%s\n", cur_str);
}

void dfs(int cur_pos, char cur_str[], int count_1)
{
    if(H-count_1+cur_pos < N)
    {
        cur_str[cur_pos] = '0';
        if(cur_pos < N-1)
            dfs(cur_pos+1, cur_str, count_1);
        else
            output(cur_pos, cur_str);
    }
    if(H > 0)
    {
        cur_str[cur_pos] = '1';
        if(count_1+1 < H && cur_pos < N-1)
            dfs(cur_pos+1, cur_str, count_1+1);
        else
            output(cur_pos, cur_str);
    }
}

int main()
{
    int tc;
    char str[17];
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &N, &H);
        dfs(0, str, 0);
        if(tc)
            printf("\n");
    }
    return 0;
}