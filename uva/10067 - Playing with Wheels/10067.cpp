
#include <string.h>
#include <iostream>
#include <queue>

#define NOT_DISCOVERED 0
#define DISCOVERED 1
#define PROCESSED 2
#define FORBIDDEN 3

#define MAXV 10000

int init_num;
int target_num;

int graph[MAXV][8];

int num_status[MAXV];
int num_depth[MAXV];

int get_num(int *digit)
{
	int res = 0;
	for(int i = 3; i >= 0; i--)
		res = 10 * res + digit[i];
	return res;
}

void get_digit(int num, int *digit)
{
	for(int i = 0; i < 4; i++)
	{
		digit[i] = num % 10;
		num /= 10;
	}
}

void make_graph()
{
	int digit[4];
	int temp;
	for(int i = 0; i < MAXV; i++)
	{
		get_digit(i, digit);
		for(int j = 0; j < 4; j++)
		{
			temp = digit[j];
			if(++digit[j] > 9)
				digit[j] = 0;
			graph[i][j * 2] = get_num(digit);
			digit[j] = temp;
			if(--digit[j] < 0)
				digit[j] = 9;
			graph[i][j * 2 + 1] = get_num(digit);
			digit[j] = temp;
		}
	}
}

int bfs()
{
	int i;
	int x, y;
	std::queue<int> num_q;
	if(num_status[init_num] == FORBIDDEN || num_status[target_num] == FORBIDDEN)
		return -1;
	if(init_num == target_num)
		return 0;
	num_status[init_num] = DISCOVERED;
	num_q.push(init_num);
	num_depth[init_num] = 0;
	while(!num_q.empty())
	{
		x = num_q.front();
		num_q.pop();
		for(i = 0; i < 8; i++)
		{
			y = graph[x][i];
			if(y == target_num)
				return num_depth[x] + 1;
			if(num_status[y] != DISCOVERED && num_status[y] != PROCESSED && num_status[y] != FORBIDDEN)
			{
				num_status[y] = DISCOVERED;
				num_depth[y] = num_depth[x] + 1;
				num_q.push(y);
			}
		}
		num_status[x] = PROCESSED;
	}
	return -1;
}

int main()
{
	int N, n;
	int digit[4];
	std::cin >> N;
	make_graph();
	while(N-- > 0)
	{
		memset(num_status, NOT_DISCOVERED, sizeof(int) * MAXV);
		memset(num_depth, -1, sizeof(int) * MAXV);
		std::cin >> digit[3] >> digit[2] >> digit[1] >> digit[0];
		init_num = get_num(digit);
		std::cin >> digit[3] >> digit[2] >> digit[1] >> digit[0];
		target_num = get_num(digit);
		std::cin >> n;
		while(n-- > 0)
		{
			std::cin >> digit[3] >> digit[2] >> digit[1] >> digit[0];
			num_status[get_num(digit)] = FORBIDDEN;
		}
		std::cout << bfs() << std::endl;
	}
	return 0;
}
