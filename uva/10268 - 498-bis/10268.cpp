#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<int> a;

int evaluate(int x)
{
    int i, r = 0, n = a.size()-1;
    for(i = 0; i < n; i++)
    {
        r = r*x+a[i]*(n-i);
    }
    return r;
}

int main()
{
    int v, x;
    std::string line;
    std::istringstream iss;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    while(std::cin >> x)
    {
        std::getline(std::cin, line);
        std::getline(std::cin, line);
        a.clear();
        iss.str(line);
        while(iss >> v)
            a.push_back(v);
        std::cout << evaluate(x) << '\n';
        iss.clear();
    }
    return 0;
}

