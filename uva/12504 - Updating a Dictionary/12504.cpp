#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::pair<std::string, std::string> kv_t;
typedef std::vector<kv_t> dict_t;

dict_t dict1, dict2;
std::vector<std::string> add, rem, chg;

void parse_dict(dict_t &d, const std::string &str)
{
    int i, j;
    kv_t item;
    d.clear();
    i = 1;
    if(str[1] == '}')
        return;
    while(i < str.length())
    {
        j = str.find_first_of(':', i);
        item.first = str.substr(i, j-i);
        i = j+1;
        j = str.find_first_of(",}", i);
        item.second = str.substr(i, j-i);
        i = j+1;
        d.push_back(item);
    }
}

bool print_ans(const std::vector<std::string> &vec, char sym)
{
    if(vec.size() > 0)
    {
        std::cout << sym << vec[0];
        for(int i = 1; i < vec.size(); ++i)
            std::cout << ',' << vec[i];
        std::cout << '\n';
        return true;
    }
    return false;
}

int main()
{
    int n;
    bool nc;
    std::string line;
    std::vector<kv_t>::const_iterator it1, it2;
    std::ios_base::sync_with_stdio(false);
    std::cin >> n;
    while(n--)
    {
        std::cin >> line;
        parse_dict(dict1, line);
        std::cin >> line;
        parse_dict(dict2, line);

        std::sort(dict1.begin(), dict1.end());
        std::sort(dict2.begin(), dict2.end());

        add.clear(), rem.clear(), chg.clear();
        it1 = dict1.begin(), it2 = dict2.begin();
        while(it1 != dict1.end() && it2 != dict2.end())
        {
            if(it1->first < it2->first)
                rem.push_back(it1++->first);
            else if(it1->first > it2->first)
                add.push_back(it2++->first);
            else
            {
                if(it1->second != it2->second)
                    chg.push_back(it1->first);
                ++it1, ++it2;
            }
        }
        while(it1 != dict1.end())
            rem.push_back(it1++->first);
        while(it2 != dict2.end())
            add.push_back(it2++->first);

        nc = true;
        if(print_ans(add, '+'))
            nc = false;
        if(print_ans(rem, '-'))
            nc = false;
        if(print_ans(chg, '*'))
            nc = false;
        if(nc)
            std::cout << "No changes\n";
        std::cout << '\n';
    }
    return 0;
}

