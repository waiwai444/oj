#include <cstdio>
#include <cstring>

#define MAXIDX 100000
#define MAXLEN 30000

char tmp[2][MAXLEN];

struct trie_node_t
{
    long idx;
    trie_node_t *next[10];
};

long node_cnt;
trie_node_t node_pool[40*MAXIDX], *dict;

trie_node_t *new_node(long idx)
{
    node_pool[node_cnt].idx = idx;
    return &node_pool[node_cnt++];
}

void insert_prefix(char p[], int len, long idx)
{
    int i;
    trie_node_t *t = dict;
    for(i = len-1; i >= 0; --i)
    {
        if(!t->next[p[i]])
            t->next[p[i]] = new_node(idx);
        t = t->next[p[i]];
    }
}

long find_idx_by_char(char str[])
{
    char *p = str;
    trie_node_t *t = dict;
    while(*p)
        if(!(t = t->next[*p++-'0']))
            return -1;
    return t->idx;
}

void init()
{
    long i, j, k, l, t = 0, c;
    dict = new_node(0);
    tmp[0][0] = tmp[1][0] = 1;
    insert_prefix(tmp[0], 1, 0);
    insert_prefix(tmp[1], 1, 1);
    k = 0, l = 1;
    for(i = 2; i < MAXIDX; ++i)
    {
        c = 0;
        for(j = k; j < l; ++j)
        {
            tmp[t][j] += tmp[1-t][j]+c;
            c = tmp[t][j] >= 10 ? tmp[t][j] -= 10, 1 : 0;
        }
        if(c)
            tmp[t][j++] = 1;
        l = j;
        if(l-k > 50)
            ++k;
        if(l < 40)
            insert_prefix(tmp[t], l, i);
        else
            insert_prefix(&tmp[t][l-40], 40, i);
        t = 1-t;
    }
}

int main()
{
    long i, t, n;
    char p[41];
    init();
    std::scanf("%ld", &t);
    for(i = 1; i <= t; ++i)
    {
        std::scanf("%s", p);
        n = find_idx_by_char(p);
        std::printf("Case #%ld: %ld\n", i, n);
    }
    return 0;
}

