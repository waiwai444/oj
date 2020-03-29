#include <stdio.h>

int n, L;
int cnt;
char seq[81], out_buf[101];

bool check_repeat(int cur)
{
    int i, j, k = cur/2;
    for(i = cur-1; i >= k; i--)
    {
        for(j = 0; cur-j > i; j++)
        {
            if(seq[cur-j] != seq[i-j])
                break;
        }
        if(i+j == cur)
            return true;
    }
    return false;
}

void output(int cur)
{
    int i, j;
    for(i = j = 0; i <= cur; i++)
    {
        if(i > 0 && i%4 == 0)
        {
            if(i%64 == 0)
                out_buf[j++] = '\n';
            else
                out_buf[j++] = ' ';
        }
        out_buf[j++] = seq[i];
    }
    out_buf[j] = '\0';
    printf("%s\n%d\n", out_buf, cur+1);
}

bool find(int cur)
{
    char ch;
    for(ch = 'A'; ch < 'A'+L; ch++)
    {
        if(cur > 0 && seq[cur-1] == ch)
            continue;
        seq[cur] = ch;
        if(check_repeat(cur))
            continue;
        cnt++;
        if(cnt == n)
        {
            output(cur);
            return true;
        }
        if(find(cur+1))
            return true;
    }
    return false;
}

int main()
{
    while(scanf("%d%d", &n, &L), n)
    {
        cnt = 0;
        find(0);
    }
    return 0;
}