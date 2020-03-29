#include <cstdio>

int main()
{
    int tc = 0;
    char line[8];
    while(std::fgets(line, 8, stdin))
    {
        if(line[0] == '*')
            break;
        if(line[0] == 'H')
            std::printf("Case %d: Hajj-e-Akbar\n", ++tc);
        else
            std::printf("Case %d: Hajj-e-Asghar\n", ++tc);
    }
    return 0;
}
