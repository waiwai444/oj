#include <stdio.h>
#include <string.h>

int edge_num;
int indegree_num[26], outdegree_num[26];

int disjoint_set[26];
int rank[26];
int set_num;

void init_disjoint_set()
{
    int i;
    set_num = 26;
    for(i = 0; i < 26; i++)
    {
        disjoint_set[i] = i;
        rank[i] = 0;
    }
}

int find_root(int node)
{
    int p = disjoint_set[node];
    return disjoint_set[p] == p ? p : disjoint_set[node] = find_root(p);
}

void union_set(int node1, int node2)
{
    int r1 = find_root(node1);
    int r2 = find_root(node2);
    if(r1 == r2)
        return;
    if(rank[r1] > rank[r2])
        disjoint_set[r2] = r1;
    else if(rank[r2] > rank[r1])
        disjoint_set[r1] = r2;
    else
    {
        disjoint_set[r2] = r1;
        rank[r1]++;
    }
    set_num--;
}

bool check_euler_path()
{
    int i, start_node = -1, end_node = -1, invalid_node_num = 0;
    for(i = 0; i < 26; i++)
    {
        if(indegree_num[i] == outdegree_num[i])
        {
            if(indegree_num[i] == 0)
                invalid_node_num++;
            continue;
        }
        if(outdegree_num[i]-indegree_num[i] == 1)
        {
            if(start_node != -1)
                return false;
            start_node = i;
        }
        else if(indegree_num[i]-outdegree_num[i] == 1)
        {
            if(end_node != -1)
                return false;
            end_node = i;
        }
        else
            return false;
    }
    if((start_node != -1 && end_node == -1) || (start_node == -1 && end_node != -1))
        return false;
    return set_num-invalid_node_num == 1;
}

int main()
{
    int i, tc;
    char word[1001];
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &edge_num);
        memset(indegree_num, 0, sizeof(indegree_num));
        memset(outdegree_num, 0, sizeof(outdegree_num));
        init_disjoint_set();
        for(i = 0; i < edge_num; i++)
        {
            scanf("%s", word);
            int from_node = word[0]-'a';
            int to_node = word[strlen(word)-1]-'a';
            indegree_num[to_node]++;
            outdegree_num[from_node]++;
            union_set(from_node, to_node);
            
        }
        if(check_euler_path())
            printf("Ordering is possible.\n");
        else
            printf("The door cannot be opened.\n");
    }
    return 0;
}