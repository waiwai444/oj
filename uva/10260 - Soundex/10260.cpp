#include <cstdio>

char map[26] = { 0, '1', '2', '3', 0, '1', '2', 0, 0, '2', '2', '4', '5', '5', 0, '1', '2', '6', '2', '3', 0, '1', 0, '2', 0, '2' };

int main()
{
    char word[21], code[21];
    char *p, *q, d;
    while(scanf("%s", word) != EOF)
    {
        p = word, q = code;
        while(*p != '\0')
        {
            d = map[*p-'A'];
            if(d && (p == word || d != map[*(p-1)-'A']))
                *q++ = d;
            ++p;
        }
        *q = '\0';
        printf("%s\n", code);
    }
    return 0;
}

