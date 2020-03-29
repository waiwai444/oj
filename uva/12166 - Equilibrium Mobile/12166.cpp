#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#define MAXN 131100

struct node_t
{
    std::vector<std::pair<long long, long> > vp;
    node_t *ch[2];
} nd[MAXN], *rt;
long nn;

long read_num(const char *&str)
{
    long val = 0;
    while(std::isdigit(*str))
        val = 10*val+(*str++)-'0';
    return val;
}

node_t *create_tree(const char *&str)
{
    long i = nn++;
    nd[i].vp.clear();
    if(std::isdigit(*str))
    {
        nd[i].vp.push_back(std::make_pair(read_num(str), 0));
        nd[i].ch[0] = nd[i].ch[1] = NULL;
    }
    else if(*str == '[')
    {
        nd[i].ch[0] = create_tree(++str);
        nd[i].ch[1] = create_tree(++str);
		++str;
    }
    return &nd[i];
}

long traverse(node_t *pn)
{
    if(!pn->ch[0])
        return 1;
    long n1 = traverse(pn->ch[0]);
    long n2 = traverse(pn->ch[1]);
    std::vector<std::pair<long long, long> > &vp1 = pn->ch[0]->vp;
    std::vector<std::pair<long long, long> > &vp2 = pn->ch[1]->vp;
    int i = 0, j = 0;
    while(i < vp1.size() && j < vp2.size())
    {
        if(vp1[i].first < vp2[j].first)
        {
            pn->vp.push_back(std::make_pair(2*vp1[i].first, vp1[i].second+n2));
            ++i;
        }
        else if(vp1[i].first > vp2[j].first)
        {
            pn->vp.push_back(std::make_pair(2*vp2[j].first, vp2[j].second+n1));
            ++j;
        }
        else
        {
            pn->vp.push_back(std::make_pair(2*vp1[i].first, vp1[i].second+vp2[j].second));
            ++i, ++j;
        }
    }
    while(i < vp1.size())
    {
        pn->vp.push_back(std::make_pair(2*vp1[i].first, vp1[i].second+n2));
        ++i;
    }
    while(j < vp2.size())
    {
        pn->vp.push_back(std::make_pair(2*vp2[j].first, vp2[j].second+n1));
        ++j;
    }
    return n1+n2;
}

long solve()
{
    traverse(rt);
    long i, r = MAXN;
    for(i = 0; i < rt->vp.size(); ++i)
        if(r > rt->vp[i].second)
            r = rt->vp[i].second;
    return r;
}

int main()
{
    int tc;
    const char *p;
    std::string line;
    std::ios_base::sync_with_stdio(false);
    std::cin >> tc;
    std::getline(std::cin, line);
    while(tc--)
    {
        std::getline(std::cin, line);
        nn = 0;
        p = line.c_str();
        rt = create_tree(p);
        std::cout << solve() << '\n';
    }
    return 0;
}

