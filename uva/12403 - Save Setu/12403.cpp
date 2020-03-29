#include <cstdio>

int main()
{
    int t, n, s = 0;
    char op[8];
    std::scanf("%d", &t);
    while(t--)
    {
        std::scanf("%s", op);
        if(op[0] == 'd')
        {
            std::scanf("%d", &n);
            s += n;
        }
        else
            std::printf("%d\n", s);
    }
    return 0;
}
