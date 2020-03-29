#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int nl;
std::vector<std::string> lines[1000];
std::vector<int> width;

int main()
{
    int i, j;
    std::string line, word;
    std::istringstream iss;
    std::ios_base::sync_with_stdio(false);
    for(i = 0; i < 1000; ++i)
        lines[i].reserve(100);
    width.reserve(100);
    while(std::getline(std::cin, line))
    {
        if(line[0] == '\0')
            continue;
        iss.clear(), iss.str(line);
        while(!iss.eof())
            if(iss >> word)
                lines[nl].push_back(word);
        ++nl;
    }
    for(i = 0; i < nl; ++i)
    {
        if(width.size() < lines[i].size())
            width.resize(lines[i].size());
        for(j = 0; j < lines[i].size(); ++j)
            width[j] = std::max((int)lines[i][j].length()+1, width[j]);
    }
    std::cout << std::setiosflags(std::ios::left);
    for(i = 0; i < nl; ++i)
    {
        for(j = 0; j < lines[i].size()-1; ++j)
            std::cout << std::setw(width[j]) << lines[i][j];
        std::cout << lines[i][lines[i].size()-1] << std::endl;
    }
    return 0;
}

