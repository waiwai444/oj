#include <cstdio>

long n;
bool rev;

struct node_t
{
    long num;
    node_t *prev, *next;
};

node_t list[100002];

inline void move_to_left(node_t *x, node_t *y)
{
    if(x->next == y)
        return;
    node_t *px = x->prev, *nx = x->next, *py = y->prev;
    px->next = nx, nx->prev = px;
    x->next = y, y->prev = x;
    py->next = x, x->prev = py;
}

inline void move_to_right(node_t *x, node_t *y)
{
    if(y->next == x)
        return;
    node_t *px = x->prev, *nx = x->next, *ny = y->next;
    px->next = nx, nx->prev = px;
    y->next = x, x->prev = y;
    x->next = ny, ny->prev = x;
}

inline void swap(node_t *x, node_t *y)
{
    if(x->next == y)
        move_to_right(x, y);
    else if(y->next == x)
        move_to_left(x, y);
    else
    {
        node_t *px = x->prev, *nx = x->next, *py = y->prev, *ny = y->next;
        px->next = y, y->prev = px;
        y->next = nx, nx->prev = y;
        py->next = x, x->prev = py;
        x->next = ny, ny->prev = x;
    }
}

inline unsigned long get_odd_sum()
{
    node_t *p = list[0].next;
    unsigned long res = 0;
    if(rev && n%2 == 0)
        p = p->next;
    while(p && p->num > 0)
    {
        res += p->num;
        p = p->next->next;
    }
    return res;
}

int main()
{
    int c, tc = 0;
    long i, m, x, y;
    while(std::scanf("%ld%ld", &n, &m) != EOF)
    {
        rev = false;
        for(i = 1; i <= n+1; ++i)
            list[i].num = i, list[i].prev = &list[i-1], list[i-1].next = &list[i];
        list[0].num = list[n+1].num = 0, list[n+1].next = NULL;
        for(i = 0; i < m; ++i)
        {
            std::scanf("%d", &c);
            if(c < 4)
                std::scanf("%ld%ld", &x, &y);
            if((c == 1 && !rev) || (c == 2 && rev))
                move_to_left(&list[x], &list[y]);
            else if((c == 2 && !rev) || (c == 1 && rev))
                move_to_right(&list[x], &list[y]);
            else if(c == 3)
                swap(&list[x], &list[y]);
            else
                rev = !rev;
        }
        std::printf("Case %d: %lu\n", ++tc, get_odd_sum());
    }
    return 0;
}

