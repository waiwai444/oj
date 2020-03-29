#include <cstdio>

int main()
{
    unsigned int x, y;
    while(std::scanf("%u%u", &x, &y) != EOF)
        std::printf("%u\n", x^y);
    return 0;
}
