#include <cstdio>

void print_recur(int x)
{
    if(x == 0)
        return;
    print_recur(x/3);
    std::putchar(x%3+'0');
}

int main()
{
    int n;
    while(std::scanf("%d", &n) && n >= 0)
    {
        if(n == 0)
            std::putchar('0');
        else
            print_recur(n);
        std::putchar('\n');
    }
    return 0;
}
