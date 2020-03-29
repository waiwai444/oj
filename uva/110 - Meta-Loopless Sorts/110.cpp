#include <stdio.h>

int n;

struct LinkNode
{
    char ch;
    LinkNode *prev, *next;
} link_list[8], *list_front, *list_back;

inline void indent(int level)
{
    printf("%*c", 2*level, ' ');
}

inline void init_link_list()
{
    for(int i = 0; i < 8; i++)
        link_list[i].ch = 'a'+i;
}

void insert_node(LinkNode* list_ptr, LinkNode* node, bool prev) // list not empty
{
    if(!prev)
    {
        node->prev = list_ptr;
        node->next = list_ptr->next;
        list_ptr->next = node;
        if(node->next)
            node->next->prev = node;
        if(list_back == list_ptr)
            list_back = node;
    }
    else
    {
        node->prev = list_ptr->prev;
        node->next = list_ptr;
        list_ptr->prev = node;
        if(node->prev)
            node->prev->next = node;
        if(list_front == list_ptr)
            list_front = node;
    }
}

void remove_node(LinkNode* node)    // at least two nodes in list
{
    if(node->prev)
        node->prev->next = node->next;
    if(node->next)
        node->next->prev = node->prev;
    if(list_front == node)
        list_front = node->next;
    if(list_back == node)
        list_back = node->prev;
}

void recursive(int cur)
{
    LinkNode* ptr;
    
    if(cur == n)
    {
        indent(cur);
        printf("writeln(%c", list_front->ch);
        ptr = list_front->next;
        while(ptr)
        {
            printf(",%c", ptr->ch);
            ptr = ptr->next;
        }
        printf(")\n");
        return;
    }
    
    indent(cur);
    printf("if %c < %c then\n", list_back->ch, 'a'+cur);
    insert_node(list_back, &link_list[cur], false);
    recursive(cur+1);
    remove_node(&link_list[cur]);
    
    for(ptr = list_back->prev; ptr != 0; ptr = ptr->prev)
    {
        indent(cur);
        printf("else if %c < %c then\n", ptr->ch, 'a'+cur);
        insert_node(ptr, &link_list[cur], false);
        recursive(cur+1);
        remove_node(&link_list[cur]);
    }
    
    indent(cur);
    printf("else\n");
    insert_node(list_front, &link_list[cur], true);
    recursive(cur+1);
    remove_node(&link_list[cur]);
}

void generate()
{
    int i;
    printf("program sort(input,output);\n" "var\n" "a");
    for(i = 1; i < n; i++)
        printf(",%c", 'a'+i);
    printf(" : integer;\n" "begin\n" "  readln(a");
    for(i = 1; i < n; i++)
        printf(",%c", 'a'+i);
    printf(");\n");
    if(n == 1)
        printf("  writeln(a)\n");
    else
    {
        list_front = list_back = &link_list[0];
        link_list[0].prev = link_list[0].next = 0;
        recursive(1);
    }
    printf("end.\n");
}

int main()
{
    int M;
    scanf("%d", &M);
    init_link_list();
    while(M--)
    {
        scanf("%d", &n);
        generate();
        if(M)
            printf("\n");
    }
    return 0;
}