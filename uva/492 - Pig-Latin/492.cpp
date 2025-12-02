#include <ctype.h>
#include <iostream>
#include <string>

inline bool is_vowel(char ch)
{
    return ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' || ch == 'i' || ch == 'I' || ch == 'o' ||  ch == 'O' || ch == 'u' || ch == 'U';
}

int main()
{
    std::string line, newline, s;
    std::ios_base::sync_with_stdio(false);
    s.reserve(5);
    while(std::getline(std::cin, line))
    {
        newline.clear();
        newline.reserve(line.size()*2);
        for(auto ch : line)
        {
            if(!isalpha(ch))
            {
                if(!s.empty())
                {
                    newline.append(s);
                    s.clear();
                }
                newline.push_back(ch);
            }
            else
            {
                if(s.empty())
                {
                    if(!is_vowel(ch))
                        s = ch;
                    else
                        newline.push_back(ch);
                    s.append("ay");
                }
                else
                    newline.push_back(ch);
            }
        }
        if(!s.empty())
        {
            newline.append(s);
            s.clear();
        }
        std::cout << newline << std::endl;
    }
    return 0;
}
