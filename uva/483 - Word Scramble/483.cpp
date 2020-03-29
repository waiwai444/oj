#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    int p, q;
    std::string line;
    while(std::getline(std::cin, line))
    {
        p = line.find_first_not_of(' ');
        while(p < line.size())
        {
            q = line.find_first_of(' ', p);
            if(q == std::string::npos)
                q = line.size();
            std::reverse(line.begin()+p, line.begin()+q);
            p = line.find_first_not_of(' ', q);
        }
        std::cout<<line<<std::endl;
    }
    return 0;
}
