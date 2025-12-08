#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int n;
struct employee_t
{
    std::string name;
    int boss;
    std::vector<int> subs;
} emp[201];

int max[201][2];
char uniq[201][2];

void traverse(int r)
{
    max[r][0] = 0;
    max[r][1] = 1;
    uniq[r][0] = uniq[r][1] = 1;
    if(emp[r].subs.size() == 0)
        return;
    for(auto i : emp[r].subs)
    {
        traverse(i);
        if(max[i][0] > max[i][1])
        {
            max[r][0] += max[i][0];
            uniq[r][0] &= uniq[i][0];
        }
        else if(max[i][0] < max[i][1])
        {
            max[r][0] += max[i][1];
            uniq[r][0] &= uniq[i][1];
        }
        else
        {
            max[r][0] += max[i][0];
            uniq[r][0] = 0;
        }
        max[r][1] += max[i][0];
        uniq[r][1] &= uniq[i][0];
    }
}

int main()
{
    int i, j;
    std::string en, bn;
    std::unordered_map<std::string, int> idx;
    std::ios_base::sync_with_stdio(false);
    while((std::cin >> n) && n)
    {
        idx.clear();
        std::cin >> emp[0].name;
        idx[emp[0].name] = 0;
        for(i = j = 1; i < n; ++i)
        {
            std::cin >> en >> bn;
            if(idx.find(en) == idx.end())
            {
                emp[j].name = en;
                idx[en] = j++;
            }
            if(idx.find(bn) == idx.end())
            {
                emp[j].name = bn;
                idx[bn] = j++;
            }
            emp[idx[en]].boss = idx[bn];
            emp[idx[bn]].subs.push_back(idx[en]);
        }
        traverse(0);
        if(max[0][0] < max[0][1])
            std::cout << max[0][1] << (uniq[0][1] ? " Yes\n" : " No\n");
        else if(max[0][0] > max[0][1])
            std::cout << max[0][0] << (uniq[0][0] ? " Yes\n" : " No\n");
        else
            std::cout << max[0][0] << " No\n";
        for(i = 0; i < n; ++i)
            emp[i].subs.clear();
    }
    return 0;
}
