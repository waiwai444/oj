#include <algorithm>
#include <cctype>
#include <iostream>

int get_value(const std::string &name)
{
    int i, s = 0, t;
    for(i = 0; i < name.size(); ++i)
        if(std::isalpha(name[i]))
            s += std::tolower(name[i])-'a'+1;
    while(s >= 10)
    {
        t = s, s = 0;
        while(t)
        {
            s += t%10;
            t /= 10;
        }
    }
    return s;
}

int main()
{
    int i, s1, s2;
    std::string line;
    while(std::getline(std::cin, line))
    {
        s1 = get_value(line);
        std::getline(std::cin, line);
        s2 = get_value(line);
        if(s1 > s2)
            std::swap(s1, s2);
        std::printf("%.2lf %%\n", (double)s1/s2*100);
    }
    return 0;
}
