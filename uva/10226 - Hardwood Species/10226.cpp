#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <map>

int main()
{
    int tc, c;
    std::string line;
    std::map<std::string, int> dict;
    std::ios_base::sync_with_stdio(false);
    std::cin >> tc;
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::cout << std::fixed << std::setprecision(4);
    while(tc--)
    {
        c = 0;
        dict.clear();
        while(std::getline(std::cin, line))
        {
            if(line.size() == 0)
                break;
            ++dict[line];
            ++c;
        }
        for(auto &p : dict)
        {
            std::cout << p.first << ' ' << (double)p.second*100/c << std::endl;
        }
        if(tc)
            std::cout << std::endl;
    }
    return 0;
}
