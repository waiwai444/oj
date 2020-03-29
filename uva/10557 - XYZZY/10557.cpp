#include <stdio.h>
#include <string.h>

#define INIT_ENERGY 100
#define INF 0x3f3f3f3f

struct edge_link
{
    int to;
    int next;
};

int room_num;
int room_energy[100];
edge_link edge_set[100*100];
int edge_list_head[100];
edge_link edge_set_r[100*100];
int edge_list_head_r[100];

int lower_bound[100];
bool on_path[100];
int path_energy[100];

void check_reachable()
{
    int que[101], front, back;
    int cur_room, next_room, edge_idx;
    front = back = 0;
    int i;
    for(i = 0; i < room_num; i++)
        lower_bound[i] = INF;
    lower_bound[room_num-1] = 0;
    que[back++] = room_num-1;
    while(front != back)
    {
        cur_room = que[front++];
        for(edge_idx = edge_list_head_r[cur_room]; edge_idx != -1; edge_idx = edge_set_r[edge_idx].next)
        {
            next_room = edge_set_r[edge_idx].to;
            if(lower_bound[next_room] == INF)
            {
                lower_bound[next_room] = 0;
                que[back++] = next_room;
            }
        }
    }
}

bool search_path(int room)
{
	int edge_idx, next_room, next_energy, lb = INF;
	for(edge_idx = edge_list_head[room]; edge_idx != -1; edge_idx = edge_set[edge_idx].next)
	{
        next_room = edge_set[edge_idx].to;
        if(next_room == room_num-1)
            return true;
        if(lower_bound[next_room] != INF)   // unreachable
        {
            if(!on_path[next_room])
            {
                next_energy = path_energy[room]+room_energy[next_room];
                if(next_energy > lower_bound[next_room])
                {
                    on_path[next_room] = true;
                    path_energy[next_room] = next_energy;
                    if(search_path(next_room))
                        return true;
                    on_path[next_room] = false;
                }
                int tmp = lower_bound[next_room]-room_energy[next_room];
                if(tmp < lb)
                    lb = tmp;
            }
            else if(path_energy[room]+room_energy[next_room]-path_energy[next_room] > 0)	// positive loop
                return true;
        }
	}
    lower_bound[room] = lb;
	return false;
}

int main()
{
	int i, j, k, edge_num;
	while(scanf("%d", &room_num), room_num != -1)
	{
		edge_num = 0;
        for(i = 0; i < room_num; i++)
            edge_list_head[i] = edge_list_head_r[i] = -1;
		for(i = 0; i < room_num; i++)
		{
			scanf("%d%d", &room_energy[i], &j);
			while(j--)
			{
				scanf("%d", &k);
				edge_set[edge_num].to = k-1;
                edge_set[edge_num].next = edge_list_head[i];
                edge_list_head[i] = edge_num;
                edge_set_r[edge_num].to = i;
                edge_set_r[edge_num].next = edge_list_head_r[k-1];
                edge_list_head_r[k-1]=edge_num;
                edge_num++;
			}
		}
        if(room_num == 1)
        {
            printf("winnable\n");
            continue;
        }
        check_reachable();
        if(lower_bound[0] == INF)
        {
            printf("hopeless\n");
            continue;
        }
        memset(on_path, false, room_num*sizeof(bool));
        on_path[0] = true;
        path_energy[0] = INIT_ENERGY;
        if(search_path(0))
            printf("winnable\n");
        else
            printf("hopeless\n");
	}
	return 0;
}