#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
#include <queue>

#define MOVE 0
#define SWITCH_ON 1
#define SWITCH_OFF 2

struct Event
{
    int type;
    int arg;
};

struct State
{
	int room;
	int light_state;
};

bool operator<(const State &s1, const State &s2)
{
	if(s1.room < s2.room)
		return true;
	else if(s1.room > s2.room)
		return false;
	return s1.light_state < s2.light_state;
}

struct Room
{
	std::vector<int> light_switch;
} room[11];

bool door[11][11];
int r, d, s;
std::set<State> state_set;

inline bool finished(const State &state)
{
    return state.room == r && state.light_state == (1<<(r-1));
}

bool bfs(std::vector<Event> &result_path)
{
	int i, j;
	std::queue<State> sq;
	std::queue<std::vector<Event> > pq;
	State state, new_state;
	std::vector<Event> path;
	Event event;

	state.room = 1;
	state.light_state = 1;
	if(finished(state))
	{
		result_path.clear();
		return true;
	}
	sq.push(state);
	pq.push(path);

	while(!sq.empty())
	{
		state = sq.front();
		sq.pop();
		path.swap(pq.front());
		pq.pop();

		for(i = 0; i < room[state.room].light_switch.size(); i++)	// switch on or off lights
		{
			j = room[state.room].light_switch[i];
			if(state.room == j)	// don't switch the light in the current room
				continue;
			new_state = state;
			new_state.light_state ^= 1<<(j-1);
			if(state_set.insert(new_state).second == true)
			{
				sq.push(new_state);
				event.type = new_state.light_state&1<<(j-1) ? SWITCH_ON : SWITCH_OFF;
				event.arg = j;
                path.push_back(event);
                if(finished(new_state))
				{
					result_path = path;
					return true;
				}
                pq.push(path);
                path.pop_back();
			}
		}

		for(i = 1; i <= r; i++)	// move
		{
            if(!door[state.room][i] || !(state.light_state&1<<(i-1)))
				continue;
			new_state = state;
			new_state.room = i;
			if(state_set.insert(new_state).second == true)
			{
                sq.push(new_state);
                event.type = MOVE;
                event.arg = i;
                path.push_back(event);
                if(finished(new_state))
				{
					result_path = path;
					return true;
				}
                pq.push(path);
                path.pop_back();
			}
		}
	}

	return false;
}

void print_result(const std::vector<Event> &result_path)
{
	for(int i = 0; i < result_path.size(); i++)
	{
		switch(result_path[i].type)
		{
		case MOVE:
            printf("- Move to room %d.\n", result_path[i].arg);
            break;
		case SWITCH_ON:
			printf("- Switch on light in room %d.\n", result_path[i].arg);
			break;
		case SWITCH_OFF:
			printf("- Switch off light in room %d.\n", result_path[i].arg);
		}
	}
}

int main()
{
	int i, t1, t2, tc(0);
	std::vector<Event> result_path;
	while(scanf("%d%d%d", &r, &d, &s), r)
	{
		memset(door, false, sizeof(door));
		state_set.clear();
        for(i = 0; i < d; i++)
		{
			scanf("%d%d", &t1, &t2);
			door[t1][t2] = door[t2][t1] = true;
		}
		for(i = 1; i <= r; i++)
			room[i].light_switch.clear();
		for(i = 0; i < s; i++)
		{
            scanf("%d%d", &t1, &t2);
            room[t1].light_switch.push_back(t2);
		}

		printf("Villa #%d\n", ++tc);
		if(bfs(result_path))
		{
			printf("The problem can be solved in %d steps:\n", result_path.size());
            print_result(result_path);
		}
		else
			printf("The problem cannot be solved.\n");
		printf("\n");
	}
	return 0;
}
