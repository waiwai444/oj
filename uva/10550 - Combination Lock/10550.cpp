#include <cstdio>

int main()
{
    int s, a, b, c, d;
    while(std::scanf("%d%d%d%d", &a, &b, &c, &d) != EOF)
    {
        if(a == 0 && b == 0 && c == 0 && d == 0)
            break;
        s = 80;
        s += a-b;
        if(a < b)
            s += 40;
        s += 40;
        s += c-b;
        if(c < b)
            s += 40;
        s += c-d;
        if(c < d)
            s += 40;
        std::printf("%d\n", s*9);
    }
    return 0;
}
