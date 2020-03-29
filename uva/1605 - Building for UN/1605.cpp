#include <cstdio>
#include <cstring>

int n;

#define GET_CHAR(i) ((i) < 26 ? 'A' + (i) : 'a' + (i) - 26)

int main()
{
    bool firstcase = true;
    char line[51];
    while(std::scanf("%d", &n) != EOF)
    {
        if (!firstcase)
            std::putchar('\n');
        else
            firstcase = false;
        std::printf("%d %d 2\n", n, n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                std::printf("%c", GET_CHAR(j));
            std::putchar('\n');
            std::memset(line, GET_CHAR(i), n);
            line[n] = '\0';
            std::puts(line);
            if (i < n - 1)
                std::putchar('\n');
        }
    }
    return 0;
}