#include <cctype>
#include <iostream>
#include <string>

int main()
{
    int i, j;
    std::ios::sync_with_stdio(false);
    std::string line;
    while(std::getline(std::cin, line))
    {
        if(line == "DONE")
            break;
        for(i = 0, j = line.size()-1; i < j; ++i, --j)
        {
            while(i < j && !std::isalpha(line[i]))
                ++i;
            while(i < j && !std::isalpha(line[j]))
                --j;
            if(std::tolower(line[i]) != std::tolower(line[j]))
                break;
        }
        if(i >= j)
            std::cout<<"You won't be eaten!"<<std::endl;
        else
            std::cout<<"Uh oh.."<<std::endl;
    }
    return 0;
}
