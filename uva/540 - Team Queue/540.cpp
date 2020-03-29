#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct link_node
{
	int elem;
	link_node *next;
};

int element_team[1000000];
int t;
link_node *team_last[1000];

link_node team_queue[200010];
link_node *queue_front, *queue_back;
int queue_last_pos;
int queue_size;

void init_queue()
{
	queue_last_pos = 1;
	queue_size = 0;
}

void enqueue(int elem)
{
	int team = element_team[elem];
	link_node *ptr = &team_queue[queue_last_pos++];
	ptr->elem = elem;
	if(queue_size == 0)
	{
		queue_front = queue_back = ptr;
	}
	else if(team_last[team] == 0)
	{
		queue_back->next = ptr;
		queue_back = ptr;
		ptr->next = 0;
	}
	else
	{
		ptr->next = team_last[team]->next;
		team_last[team]->next = ptr;
		if(team_last[team] == queue_back)
			queue_back = ptr;
	}
	team_last[team] = ptr;
	queue_size++;
}

int pop()
{
	if(queue_size <= 0)
		return -1;
	int ret = queue_front->elem;
	int team = element_team[ret];
	if(team_last[team] == queue_front)
		team_last[team] = 0;
	queue_front = queue_front->next;
	queue_size--;
	return ret;
}

char input_buf[10001];
char output_buf[800000], *output_ptr;

int main()
{
	int i, j, n, e, tc = 0;
	while(scanf("%d", &t), t)
	{
		fgets(input_buf, sizeof(input_buf), stdin);
		for(i = 0; i < t; i++)
		{
			fgets(input_buf, sizeof(input_buf), stdin);
			n = atoi(strtok(input_buf, " "));
			for(j = 0; j < n; j++)
			{
				e = atoi(strtok(NULL, " "));
				element_team[e] = i;
			}
		}
		init_queue();
		memset(team_last, 0, sizeof(team_last));
		output_ptr = output_buf+sprintf(output_buf, "Scenario #%d\n", ++tc);
		while(fgets(input_buf, sizeof(input_buf), stdin))
		{
			if(input_buf[0] == 'S')
				break;
			if(input_buf[0] == 'E')
			{
				sscanf(input_buf, "%*s%d", &e);
				enqueue(e);
			}
			else	// DEQUEUE
			{
				e = pop();
				if(e >= 0)
				{
					int tmp = sprintf(output_ptr, "%d\n", e);
					output_ptr += tmp;
				}
			}
		}
		printf("%s\n", output_buf);
	}
	return 0;
}
