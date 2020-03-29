#include <stdio.h>
#include <string.h>

#define INF 0x7fffffff

int node_num;
bool graph[26][26];
bool in_graph[26];

int min_bw;
char result_seq[8];
char seq[8];
int pos[26];

void parse_input(char in_buf[])
{
    int i = 0;
    char from, to;
    memset(in_graph, false, sizeof(in_graph));
    memset(graph, false, sizeof(graph));
    node_num = 0;
    while(in_buf[i] != '\0')
    {
        from = in_buf[i];
        if(!in_graph[from-'A'])
        {
            in_graph[from-'A'] = true;
            node_num++;
        }
        i += 2;
        while(in_buf[i] != '\0' && in_buf[i] != ';')
        {
            to = in_buf[i++];
            if(!in_graph[to-'A'])
            {
                in_graph[to-'A'] = true;
                node_num++;
            }
            graph[from-'A'][to-'A'] = graph[to-'A'][from-'A'] = true;
        }
        if(in_buf[i] == ';')
            i++;
    }
}

int cal_bandwidth(int node, int cur)
{
    int i;
    int bw = 0;
    for(i = 0; i < cur; i++)
    {
        if(graph[node][seq[i]])
        {
            bw = cur-i;
            break;
        }
    }
    return bw;
}

int other_adj_node(int node)    // those adjcent nodes that are not placed before
{
    int cnt = 0;
    for(int i = 0; i < 26; i++)
        if(node != i && graph[node][i] && pos[i] == -1)
            cnt++;
    return cnt;
}

void permute(int cur, int cur_max_bw)
{
    int i, bw;
    for(i = 0; i < 26; i++)
    {
        if(in_graph[i] && pos[i] == -1)
        {
            bw = cal_bandwidth(i, cur);
            if(bw >= min_bw)
                continue;
            if(other_adj_node(i) >= min_bw)
                continue;
            seq[cur] = i;
            pos[i] = cur;
            if(cur == node_num-1)
            {
                min_bw = bw > cur_max_bw ? bw : cur_max_bw;
                memcpy(result_seq, seq, node_num);
            }
            else
            {
                permute(cur+1, bw > cur_max_bw ? bw : cur_max_bw);
            }
            pos[i] = -1;
            if(cur_max_bw >= min_bw)
                return;
        }
    }
}

void output()
{
    int i;
    for(i = 0; i < node_num; i++)
        printf("%c ", result_seq[i]+'A');
    printf("-> %d\n", min_bw);
}

int main()
{
    char in_buf[100];
    while(scanf("%s", in_buf), in_buf[0] != '#')
    {
        parse_input(in_buf);
        min_bw = INF;
        memset(pos, -1, sizeof(pos));
        permute(0, 0);
        output();
    }
    return 0;
}