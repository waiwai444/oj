#include <set>
#include <stdio.h>

int L, P;
struct pos_t {
    int prev;
    int next;
    int ovl;
    int cov;
} pos[1000010];
int first, count;

inline bool in_range(int start, int end, int pos)
{
    if(end >= start)
        return pos >= start && pos <= end;
    return pos >= start || pos <= end;
}

inline void remove_node(int idx)
{
    pos[pos[idx].prev].next = pos[idx].next;
    pos[pos[idx].next].prev = pos[idx].prev;
    --count;
}

bool draw_out(const std::set<int> &ov)
{
    if(ov.size() == 0)
        return true;
    auto it1 = ov.begin();
    while(it1 != ov.end())
    {
        auto it2 = it1;
        ++it2;
        if(pos[*it1].cov != pos[*it2].cov)
            return false;
        ++++it1;
    }
    for(it1 = ov.begin(); it1 != ov.end(); ++it1)
    {
        remove_node(pos[*it1].ovl);
        remove_node(*it1);
    }
    return true;
}

bool solve()
{
    std::set<int> ov;
    int i, next = -1;
    bool flag = false;

    while(count)
    {
        // Remove simple self loops and passings.
        for(i = first; count; i = next)
        {
            if(pos[i].ovl == pos[i].prev)
            {
                remove_node(pos[i].prev);
                next = pos[i].next;
                remove_node(i);
                flag = true;
            }
            else if(pos[i].cov == pos[pos[i].prev].cov && (pos[pos[i].ovl].prev == pos[pos[i].prev].ovl || pos[pos[i].ovl].next == pos[pos[i].prev].ovl))
            {
                remove_node(pos[pos[i].prev].ovl);
                remove_node(pos[i].prev);
                remove_node(pos[i].ovl);
                next = pos[i].next;
                remove_node(i);
                flag = true;
            }
            else
                next = pos[i].next;
            if(next < i)
            {
                if(!flag)
                    break;
                flag = false;
            }
        }

        // Remove complex passings.
        /*
        for(i = next; count; i = next)
        {
            ov.clear();
            j = pos[i].ovl;
            k = i;
            while(true)
            {
                k = pos[k].next;
                if(in_range(i, j, pos[k].ovl))
                    break;
                ov.insert(pos[k].ovl);
            }
            if(k != j)
                next = k;
            else
            {
                if(draw_out(ov))
                {
                    remove_node(pos[i].prev);
                    remove_node(i);
                    flag = true;
                }
                next = pos[j].next;
            }
            if(next < i)
                break;
        }
        */

        if(!flag)
            break;
    }

    return count == 0;
}

int main()
{
    int i, j, c, T, A, B;
    scanf("%d", &T);
    for(c = 1; c <= T; ++c)
    {
        scanf("%d%d", &L, &P);
        for(i = 0; i < L; ++i)
            pos[i].ovl = -1;
        for(i = 0; i < P; ++i)
        {
            scanf("%d%d", &A, &B);
            pos[A].ovl = B;
            pos[A].cov = 1;
            pos[B].ovl = A;
            pos[B].cov = 0;
        }
        for(i = 0, j = -1, first = -1; i < L; ++i)
        {
            if(pos[i].ovl >= 0)
            {
                if(first == -1)
                    first = i;
                else if(j >= 0)
                {
                    pos[j].next = i;
                    pos[i].prev = j;
                }
                j = i;
            }
        }
        pos[j].next = first;
        pos[first].prev = j;
        count = P*2;
        printf("Case #%d: %s\n", c, solve() ? "YES" : "NO");
    }
    return 0;
}
