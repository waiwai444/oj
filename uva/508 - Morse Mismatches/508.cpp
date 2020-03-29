#include <cstdio>
#include <cstring>
#include <cctype>

#define INF 0x3f3f3f3f

char mch[36][8];
struct ctx_word_t
{
    char word[15];
    char morse[81];
} ctx[100];
int nc;

struct trie_node_t
{
    int first_word, word_cnt;
    trie_node_t *child[2];
    trie_node_t *fwd, *bak;
    int fwd_dist, bak_dist;

    trie_node_t() : word_cnt(0)
    {
        child[0] = child[1] = NULL;
        fwd = bak = NULL;
    }
} root;

inline int el_idx(char ch)
{
    return ch == '.' ? 0 : 1;
}

inline int ch_idx(char ch)
{
    if(isalpha(ch))
        return ch-'A';
    return ch-'0'+'Z'-'A'+1;
}

void create_trie_tree()
{
    int i, j;
    char *p;
    trie_node_t *t;
    for(i = 0; i < nc; ++i)
    {
        t = &root;
        for(p = ctx[i].morse; *p; ++p)
        {
            j = el_idx(*p);
            if(!t->child[j])
                t->child[j] = new trie_node_t;
            t = t->child[j];
        }
        if(t->word_cnt)
            ++t->word_cnt;
        else
        {
            t->first_word = i;
            t->word_cnt = 1;
        }
    }
}

trie_node_t *dfs(trie_node_t *r, trie_node_t *bak, int bak_dist, int *fwd_dist)
{
    int i, j;
    if(!r)
    {
        *fwd_dist = INF;
        return NULL;
    }
    if(r->word_cnt)
        r->bak = r, r->bak_dist = 0;
    else
        r->bak = bak, r->bak_dist = bak_dist;
    trie_node_t *t1 = dfs(r->child[0], r->bak, r->bak_dist+1, &i);
    trie_node_t *t2 = dfs(r->child[1], r->bak, r->bak_dist+1, &j);
    if(r->word_cnt)
        r->fwd = r, r->fwd_dist = 0;
    else
        r->fwd = (i <= j ? t1 : t2), r->fwd_dist = (i <= j ? i : j);
    *fwd_dist = r->fwd_dist+1;
    return r->fwd;
}

void create_jmp_ptr()
{
    int i;
    dfs(root.child[0], NULL, INF, &i);
    dfs(root.child[1], NULL, INF, &i);
}

void decode(const char *code)
{
    int i;
    const char *p;
    trie_node_t *t = &root;
    for(p = code; *p; ++p)
    {
        i = el_idx(*p);
        if(t->child[i])
            t = t->child[i];
        else
            break;
    }
    if(!*p)
    {
        if(t->word_cnt == 0)
        {
            if(t->bak_dist <= t->fwd_dist)
                printf("%s?\n", ctx[t->bak->first_word].word);
            else
                printf("%s?\n", ctx[t->fwd->first_word].word);
        }
        else if(t->word_cnt == 1)
            puts(ctx[t->first_word].word);
        else
            printf("%s!\n", ctx[t->first_word].word);
    }
    else
    {
        if(t->bak)
            printf("%s?\n", ctx[t->bak->first_word].word);
        else
            puts("?");
    }
}

int main()
{
    char tmp[81];
    while(scanf("%s", tmp), tmp[0] != '*')
        scanf("%s", mch[ch_idx(tmp[0])]);
    while(scanf("%s", tmp), tmp[0] != '*')
    {
        strcpy(ctx[nc].word, tmp);
        strcpy(ctx[nc].morse, mch[ch_idx(tmp[0])]);
        for(char *p = &tmp[1]; *p; ++p)
            strcat(ctx[nc].morse, mch[ch_idx(*p)]);
        ++nc;
    }
    create_trie_tree();
    create_jmp_ptr();
    while(scanf("%s", tmp), tmp[0] != '*')
        decode(tmp);
    return 0;
}

