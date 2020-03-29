#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<int> c;

long long evaluate(int x)
{
    int i;
    long long r = 0;
    for(i = 0; i < c.size(); i++)
    {
        r = r*x+c[i];
    }
    return r;
}

int main()
{
    int v;
    long long ans;
    std::string line;
    std::istringstream iss;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    while(std::getline(std::cin, line))
    {
        c.clear();
        iss.str(line);
        while(iss >> v)
            c.push_back(v);
        iss.clear();
        std::getline(std::cin, line);
        iss.str(line);
        bool first = true;
        while(iss >> v)
        {
            ans = evaluate(v);
            if(first)
            {
                std::cout << ans;
                first = false;
            }
            else
                std::cout << ' ' << ans;
        }
        std::cout << '\n';
        iss.clear();
    }
    return 0;
}

