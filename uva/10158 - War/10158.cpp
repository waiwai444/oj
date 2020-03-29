
#include <stdio.h>

#define MAXP 10000

// disjoint-set
int parent[MAXP];
int rank[MAXP];	// optional, for union by rank

int find_root(int x)
{
	if(parent[x] == x)
		return x;
	return parent[x] = find_root(parent[x]);
}

void union_subsets(int x, int y)
{
	int rx = find_root(x);
	int ry = find_root(y);
	if(rx != ry)
	{
		if(rank[rx] > rank[ry])
			parent[ry] = rx;
		else
		{
			parent[rx] = ry;
			if(rank[rx] == rank[ry])
				rank[ry]++;
		}
	}
}

void make_set(int n)
{
	for(int i = 0; i < n; i++)
	{
		parent[i] = i;
		rank[i] = 0;
	}
}
//

int n;
int enemy[MAXP];

bool areFriends(int x, int y)
{
	if(find_root(x) == find_root(y))
		return true;
	return false;
}

bool areEnemies(int x, int y)
{
	if(enemy[find_root(x)] == find_root(y))
		return true;
	return false;
}

bool setFriends(int x, int y)
{
	int rx = find_root(x);
	int ry = find_root(y);
	if(areEnemies(rx, ry))
		return false;	
	union_subsets(rx, ry);
	
	int erx = enemy[rx];
	int ery = enemy[ry];
	if(erx != -1 && ery != -1)
		union_subsets(erx, ery);
	
	if(erx != -1)
	{
		enemy[find_root(rx)] = find_root(erx);
		enemy[find_root(erx)] = find_root(rx);
	}
	else if(ery != -1)
	{
		enemy[find_root(rx)] = find_root(ery);
		enemy[find_root(ery)] = find_root(rx);
	}
	
	return true;
}

bool setEnemies(int x, int y)
{
	int rx = find_root(x);
	int ry = find_root(y);
	if(areFriends(rx, ry))
		return false;
	if(enemy[rx] != -1)
		setFriends(ry, enemy[rx]);
	if(enemy[ry] != -1)
		setFriends(rx, enemy[ry]);
	enemy[find_root(rx)] = find_root(ry);
	enemy[find_root(ry)] = find_root(rx);
	return true;
}

int main()
{
	int i, op, x, y;
	scanf("%d", &n);
	make_set(n);
	for(i = 0; i < n; i++)
		enemy[i] = -1;
	while(scanf("%d%d%d", &op, &x, &y))
	{
		if(op == 0)
			break;
		switch(op)
		{
			case 1:
				if(!setFriends(x, y))
					printf("-1\n");
				break;
			case 2:
				if(!setEnemies(x, y))
					printf("-1\n");
				break;
			case 3:
				if(areFriends(x, y))
					printf("1\n");
				else
					printf("0\n");
				break;
			case 4:
				if(areEnemies(x, y))
					printf("1\n");
				else
					printf("0\n");
				break;
		}
	}
	return 0;
}
