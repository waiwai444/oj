#include <algorithm>
#include <cstdio>

int main()
{
    int a, b;
    while(std::scanf("%d%d", &a, &b))
    {
        if(a == -1)
            break;
        if(a > b)
            std::swap(a, b);
        std::printf("%d\n", std::min(b-a, a+100-b));
    }
    return 0;
}
