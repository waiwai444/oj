#include <cstdio>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> pool[2001];
int ns;
int st[2000], top;

int find_set_idx(const std::vector<int> &v)
{
    for(int i = 0; i < ns; i++)
        if(v.size() == pool[i].size() && std::equal(v.begin(), v.end(), pool[i].begin()))
            return i;
    return -1;
}

int main()
{
    int i, j, t, n, s1, s2;
    char cmd[16];
    scanf("%d", &t);
    while(t--)
    {
        ns = 1, top = 0;
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
        {
            scanf("%s", cmd);
            if(cmd[0] == 'P')
                j = 0;
            else if(cmd[0] == 'D')
                j = st[top-1];
            else
            {
                pool[ns].clear();
                s1 = st[--top], s2 = st[--top];
                if(cmd[0] == 'U')
                {
                    std::set_union(pool[s1].begin(), pool[s1].end(),
                            pool[s2].begin(), pool[s2].end(),
                            std::back_inserter(pool[ns]));
                }
                else if(cmd[0] == 'I')
                {
                    std::set_intersection(pool[s1].begin(), pool[s1].end(),
                            pool[s2].begin(), pool[s2].end(),
                            std::back_inserter(pool[ns]));
                }
                else if(cmd[0] == 'A')
                {
                    std::vector<int> s(1, s1);
                    std::set_union(s.begin(), s.end(),
                            pool[s2].begin(), pool[s2].end(),
                            std::back_inserter(pool[ns]));
                }
                j = find_set_idx(pool[ns]);
                if(j < 0)
                    j = ns++;
            }
            st[top++] = j;
            printf("%lu\n", pool[st[top-1]].size());
        }
        printf("***\n");
    }
    return 0;
}

