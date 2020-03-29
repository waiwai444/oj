#include <cstdio>

int main()
{
    int a, b, c;
    while(std::scanf("%d%d%d", &a, &b, &c) != EOF)
    {
        if(a == 0)
            break;
        if(a*a+b*b == c*c || a*a+c*c == b*b || b*b+c*c == a*a)
            std::printf("right\n");
        else
            std::printf("wrong\n");
    }
    return 0;
}
