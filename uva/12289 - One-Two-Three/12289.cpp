#include <cstdio>

int main()
{
    int tc;
    char w[8];
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%s", w);
        if(w[3] != 0)
            std::puts("3");
        else if((w[0] == 'o' && w[1] == 'n')
                || (w[0] == 'o' && w[2] == 'e')
                || (w[1] == 'n' && w[2] == 'e'))
            std::puts("1");
        else
            std::puts("2");
    }
    return 0;
}
