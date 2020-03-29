#include <cstdio>
#include <cstring>
#include <algorithm>

struct order_t
{
    char type;
    long size, price;
    order_t *next;
} order[10000];

struct price_info_t
{
    long size, price;
    order_t *head, *tail;
} price_info[10000], *bid[10000], *ask[10000];

int np, nb, na;
int bid_price_idx[100000];
int ask_price_idx[100000];

void init_price_info(price_info_t *pi, long price)
{
    pi->size = 0;
    pi->price = price;
    pi->head = pi->tail = NULL;
}

order_t *new_order(int idx, char type, long size, long price)
{
    order_t *o = &order[idx];
    o->type = type;
    o->size = size;
    o->price = price;
    o->next = NULL;
    return o;
}

void enque_order(price_info_t *pi, order_t *o)
{
    pi->size += o->size;
    if(pi->tail)
    {
        pi->tail->next = o;
        pi->tail = o;
    }
    else
        pi->head = pi->tail = o;
}

void deque_order(price_info_t *pi)
{
    if(pi->head)
    {
        pi->size -= pi->head->size;
        pi->head = pi->head->next;
    }
    if(!pi->head)
        pi->tail = NULL;
}

void process_bid(int idx, long size, long price)
{
    long s, p;
    while(size > 0 && na > 0 && price >= ask[na-1]->price)
    {
        order_t *t = ask[na-1]->head;
        p = ask[na-1]->price;
        while(size > 0 && t)
        {
            s = std::min(size, t->size);
            if(s > 0)
            {
                std::printf("TRADE %ld %ld\n", s, p);
                ask[na-1]->size -= s;
                t->size -= s;
                size -= s;
            }
            if(t->size == 0)
            {
                deque_order(ask[na-1]);
                t = ask[na-1]->head;
            }
        }
        if(!t)
        {
            ask_price_idx[p] = -1;
            --na;
        }
    }
    order_t *po = new_order(idx, 'B', size, price);
    if(size > 0)
    {
        int i = bid_price_idx[price];
        if(i >= 0)
            enque_order(bid[i], po);
        else
        {
            for(i = nb-1; i >= 0 && price < bid[i]->price; --i)
            {
                bid[i+1] = bid[i];
                ++bid_price_idx[bid[i]->price];
            }
            bid[i+1] = &price_info[np++];
            init_price_info(bid[i+1], price);
            enque_order(bid[i+1], po);
            bid_price_idx[price] = i+1;
            ++nb;
        }
    }
}

void process_ask(int idx, long size, long price)
{
    long s, p;
    while(size > 0 && nb > 0 && price <= bid[nb-1]->price)
    {
        order_t *t = bid[nb-1]->head;
        p = bid[nb-1]->price;
        while(size > 0 && t)
        {
            s = std::min(size, t->size);
            if(s > 0)
            {
                std::printf("TRADE %ld %ld\n", s, p);
                bid[nb-1]->size -= s;
                t->size -= s;
                size -= s;
            }
            if(t->size == 0)
            {
                deque_order(bid[nb-1]);
                t = bid[nb-1]->head;
            }
        }
        if(!t)
        {
            bid_price_idx[p] = -1;
            --nb;
        }
    }
    order_t *po = new_order(idx, 'S', size, price);
    if(size > 0)
    {
        int i = ask_price_idx[price];
        if(i >= 0)
            enque_order(ask[i], po);
        else
        {
            for(i = na-1; i >= 0 && price > ask[i]->price; --i)
            {
                ask[i+1] = ask[i];
                ++ask_price_idx[ask[i]->price];
            }
            ask[i+1] = &price_info[np++];
            init_price_info(ask[i+1], price);
            enque_order(ask[i+1],  po);
            ask_price_idx[price] = i+1;
            ++na;
        }
    }
}

void process_cancel(int idx, int t)
{
    int i;
    new_order(idx, 'C', 0, 0);
    if(order[t].type == 'B' && (i = bid_price_idx[order[t].price]) >= 0)
        bid[i]->size -= order[t].size;
    else if(order[t].type == 'S' && (i = ask_price_idx[order[t].price]) >= 0)
        ask[i]->size -= order[t].size;
    order[t].size = 0;
}

void clear_top_invalid_orders()
{
    while(nb > 0)
    {
        while(bid[nb-1]->head && bid[nb-1]->head->size == 0)
            deque_order(bid[nb-1]);
        if(bid[nb-1]->head)
            break;
        bid_price_idx[bid[nb-1]->price] = -1;
        --nb;
    }
    while(na > 0)
    {
        while(ask[na-1]->head && ask[na-1]->head->size == 0)
            deque_order(ask[na-1]);
        if(ask[na-1]->head)
            break;
        ask_price_idx[ask[na-1]->price] = -1;
        --na;
    }
}

void print_quote()
{
    long price, size;

    clear_top_invalid_orders();

    price = size = 0;
    if(nb > 0)
        price = bid[nb-1]->price, size = bid[nb-1]->size;
    std::printf("QUOTE %ld %ld", size, price);

    price = 99999, size = 0;
    if(na > 0)
        price = ask[na-1]->price, size = ask[na-1]->size;
    std::printf(" - %ld %ld\n", size, price);
}

int main()
{
    int i, n, c;
    long q, p;
    char cmd[8];
    bool first = true;
    while(std::scanf("%d", &n) != EOF)
    {
        np = nb = na = 0;
        memset(bid_price_idx, -1, sizeof(bid_price_idx));
        memset(ask_price_idx, -1, sizeof(ask_price_idx));
        if(first)
            first = false;
        else
            std::putchar('\n');
        for(i = 0; i < n; ++i)
        {
            std::scanf("%s", cmd);
            if(cmd[0] == 'B')
            {
                std::scanf("%ld%ld", &q, &p);
                process_bid(i, q, p);
            }
            else if(cmd[0] == 'S')
            {
                std::scanf("%ld%ld", &q, &p);
                process_ask(i, q, p);
            }
            else
            {
                std::scanf("%d", &c);
                process_cancel(i, c-1);
            }
            print_quote();
        }
    }
    return 0;
}

