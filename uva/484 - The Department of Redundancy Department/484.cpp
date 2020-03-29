#include <cstdio>
#include <map>
#include <vector>

struct rec_t
{
    int num;
    int cnt;
};

int main()
{
    int n;
    std::vector<rec_t> rec;
    std::map<int, int> idx;
    while(std::scanf("%d", &n) != EOF)
    {
        std::pair<std::map<int, int>::iterator, bool> p = idx.insert(std::make_pair(n, rec.size()));
        if(!p.second)
        {
            ++rec[p.first->second].cnt;
        }
        else
        {
            rec_t r = {n, 1};
            rec.push_back(r);
        }
    }
    for(int i = 0; i < rec.size(); ++i)
    {
        std::printf("%d %d\n", rec[i].num, rec[i].cnt);
    }
    return 0;
}
