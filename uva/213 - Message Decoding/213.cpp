#include <cstdio>

char head[256];
char code[1000];

#define EOS (char)-1

enum state_e { SEGLEN, KEY };
const int p2[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

char get_ch(int len, int key)
{
    if(key == p2[len]-1)
        return EOS;
    return head[p2[len]-len-1+key];
}

void decode()
{
    char *p, ch;
    int n = 0, k = 0, c = 3;
    state_e s = SEGLEN;
    while(fgets(code, sizeof(code), stdin))
    {
        p = code;
        while(*p != '\0' && *p != '\n' && *p != '\r')
            ++p;
        *p = '\0';
        p = code;
        while(*p != '\0')
        {
            if(c == 0)
                break;
            while(c)
            {
                if(*p == '\0')
                    break;
                if(s == SEGLEN)
                    n = n*2+*p-'0';
                else
                    k = k*2+*p-'0';
                ++p, --c;
            }
            if(c == 0)
            {
                if(s == SEGLEN)
                {
                    c = n;
                    k = 0;
                    s = KEY;
                }
                else
                {
                    ch = get_ch(n, k);
                    if(ch != EOS)
                    {
                        putchar(ch);
                        c = n;
                        k = 0;
                    }
                    else
                    {
                        c = 3;
                        n = 0;
                        s = SEGLEN;
                    }
                }
            }
        }
        if(c == 0)
            break;
    }
    putchar('\n');
}

int main()
{
    while(fgets(head, sizeof(head), stdin))
    {
        if(head[0] == '\0' || head[0] == '\n' || head[0] == '\r')
            continue;
        decode();
    }
    return 0;
}

