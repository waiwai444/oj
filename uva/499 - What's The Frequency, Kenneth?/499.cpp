#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

int cnt[52];

int main()
{
    int i, max;
    std::string line;
    while(std::getline(std::cin, line))
    {
        std::memset(cnt, 0, sizeof(cnt));
        max = 0;
        for(std::string::iterator it = line.begin(); it != line.end(); ++it)
        {
            if(std::islower(*it))
                i = *it-'a'+26;
            else if(std::isupper(*it))
                i = *it-'A';
            else
                continue;
            ++cnt[i];
            if(cnt[i] > max)
                max = cnt[i];
        }
        for(i = 0; i < 26; ++i)
            if(cnt[i] == max)
                std::cout<<(char)('A'+i);
        for(; i < 52; ++i)
            if(cnt[i] == max)
                std::cout<<(char)('a'+i-26);
        std::cout<<' '<<max<<std::endl;
    }
    return 0;
}
