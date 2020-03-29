#include <stdio.h>
#include <string.h>
#include <queue>

#define RADIX 201

struct State
{
	int jug[3];
	int total;
};

int jug_cap[3], d;
int result_total, result_d;
bool visited[RADIX][RADIX];

bool operator<(State lhs, State rhs)
{
	return lhs.total > rhs.total;
}

bool finished(State state)
{
	return state.jug[0] == d || state.jug[1] == d || state.jug[2] == d;
}

bool closest_smaller(State state, int *m)
{
	int i;
	for(i = 0; i < 3; i++)
		if(state.jug[i] <= d)
		{
			*m = state.jug[i];
			break;
		}
	if(i == 3)
		return false;
	for(i++; i < 3; i++)
		if(state.jug[i] <= d && state.jug[i] > *m)
			*m = state.jug[i];
	return true;
}

State pour(State state, int from, int to)
{
	State new_state = state;
	new_state.jug[from] = state.jug[from]-(jug_cap[to]-state.jug[to]);
	if(new_state.jug[from] < 0)
	{
		new_state.jug[from] = 0;
		new_state.jug[to] = state.jug[to]+state.jug[from];
		new_state.total += state.jug[from];
	}
	else
	{
		new_state.jug[to] = jug_cap[to];
		new_state.total += jug_cap[to]-state.jug[to];
	}
	return new_state;
}

void search(State init_state)
{
	int i, j, t;
	std::priority_queue<State> Q;
	Q.push(init_state);
	visited[init_state.jug[0]][init_state.jug[1]] = true;
	State state, new_state;
	while(!Q.empty())
	{
		state = Q.top();
		Q.pop();
		if(finished(state))
		{
			result_total = state.total;
			result_d = d;
			return;
		}
		else
		{
			bool r = closest_smaller(state, &t);
			if(r && t > result_d)
			{
				result_d = t;
				result_total = state.total;
			}
		}
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(i == j)
					continue;
				new_state = pour(state, i, j);
				if(!visited[new_state.jug[0]][new_state.jug[1]])
				{
					visited[new_state.jug[0]][new_state.jug[1]] = true;
					Q.push(new_state);
				}
			}
		}
	}
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d%d%d", &jug_cap[0], &jug_cap[1], &jug_cap[2], &d);
		State state;
		state.jug[0] = state.jug[1] = 0;
		state.jug[2] = jug_cap[2];
		state.total = 0;
		result_total = 0;
		result_d = 0;
		memset(visited, false, sizeof(visited));

		search(state);

		printf("%d %d\n", result_total, result_d);
	}
	return 0;
}
