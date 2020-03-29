#include <cstdio>
#include <map>
#include <string>

int n;
char name[10][13];
std::map<std::string, int> rec;

int main()
{
    int i, j, x, m;
    char s1[13], s2[13];
    bool first = true;
    while(std::scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
        {
            std::scanf("%s", name[i]);
            rec[name[i]] = 0;
        }
        for(i = 0; i < n; ++i)
        {
            std::scanf("%s%d%d", s1, &x, &m);
            if(m)
                rec[s1] += -x/m*m;
            for(j = 0; j < m; ++j)
            {
                std::scanf("%s", s2);
                rec[s2] += x/m;
            }
        }
        if(!first)
            std::putchar('\n');
        else
            first = false;
        for(i = 0; i < n; ++i)
            std::printf("%s %d\n", name[i], rec[name[i]]);
    }
    return 0;
}
