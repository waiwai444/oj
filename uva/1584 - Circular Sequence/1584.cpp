#include <cstdio>
#include <cstring>

int main()
{
    int i, m, t, len;
    char seq[201], ans[101];
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s", seq);
        len = strlen(seq);
        for(i = 0; i < len; i++)
            seq[len+i] = seq[i];
        seq[len+i] = 0;
        for(m = 0, i = 1; i < len; i++)
            if(strncmp(&seq[m], &seq[i], len) > 0)
                m = i;
        strncpy(ans, &seq[m], len);
        ans[len] = 0;
        puts(ans);
    }
    return 0;
}

