#include <stdio.h>

struct link_node
{
    int num;
    link_node *next;
} cards[50];

int main()
{
    int i, n;
    link_node *p, *q;
    for(i = 0; i < 50; i++)
        cards[i].num = i+1;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n-1; i++)
            cards[i].next = &cards[i+1];
        cards[n-1].next = &cards[0];
        
        printf("Discarded cards:");
        q = &cards[n-1];
        p = &cards[0];
        for(i = 1; i < n; i++)
        {
            if(i < n-1)
                printf(" %d,", p->num);
            else
                printf(" %d", p->num);
            q->next = p->next;
            q = p->next;
            p = p->next->next;
        }
        printf("\nRemaining card: %d\n", p->num);
    }
    return 0;
}