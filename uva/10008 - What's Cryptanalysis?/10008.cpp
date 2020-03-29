#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int counter[26];
std::vector<std::pair<int, char> > res;

int main()
{
    int n, s = 0;
    std::string line;
    std::cin>>n;
    std::getline(std::cin, line);
    while(n--)
    {
        std::getline(std::cin, line);
        s += line.size();
        for(int i = 0; i < line.size(); ++i)
            if(std::isalpha(line[i]))
                ++counter[std::toupper(line[i])-'A'];
    }
    for(int i = 0; i < 26; ++i)
        if(counter[i])
            res.push_back(std::make_pair(s-counter[i], i+'A'));
    std::sort(res.begin(), res.end());
    for(int i = 0; i < res.size(); ++i)
        std::cout<<res[i].second<<' '<<s-res[i].first<<std::endl;
    return 0;
}
