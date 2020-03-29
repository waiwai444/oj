#include <cstdio>
#include <cctype>

const int tab[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
    7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

int main()
{
    char line[32], *p;
    while(std::fgets(line, sizeof(line), stdin))
    {
        p = line;
        while(*p)
        {
            if(std::isdigit(*p) || *p == '-')
                std::putchar(*p);
            else if(std::isalpha(*p))
                std::putchar(tab[*p-'A']+'0');
            else
                break;
            ++p;
        }
        std::putchar('\n');
    }
    return 0;
}
