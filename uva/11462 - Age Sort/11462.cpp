#include <cstdio>
#include <cctype>

int n, cnt[101];

int read_int()
{
    int ch, r = 0;
    while((ch = std::getchar()) != EOF)
        if(std::isdigit(ch))
            break;
    while(std::isdigit(ch))
    {
        r = r*10+ch-'0';
        ch = std::getchar();
    }
    return r;
}

void write_int(int x)
{
    char tmp[4], *p;
    p = tmp;
    while(x)
    {
        *p = x%10+'0';
        x /= 10;
        ++p;
    }
    while(p > tmp)
        std::putchar(*--p);
}

int main()
{
    int i, min;
    while(std::scanf("%d", &n) != EOF && n)
    {
        min = 100;
        while(n--)
        {
            i = read_int();
            ++cnt[i];
            if(i < min)
                min = i;
        }
        write_int(min);
        --cnt[min];
        for(i = min; i <= 100; ++i)
        {
            while(cnt[i] > 0)
            {
                std::putchar(' ');
                write_int(i);
                --cnt[i];
            }
        }
        std::putchar('\n');
    }
    return 0;
}
