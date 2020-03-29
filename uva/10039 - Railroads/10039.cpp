
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 100
#define MAXD 1000

// definition of hash map
#define HASH_SIZE 101

struct HashMapNode
{
	char word[100];
	size_t word_len;
	int idx;
	HashMapNode* next;
};

struct HashMap
{
	HashMapNode* vec[HASH_SIZE];
	size_t size;
};

size_t hash(char* word)	// BKDRHash
{
	unsigned int seed = 13131;
	unsigned int hash = 0;
	while(*word)
	{
		hash = hash * seed + (*word++);
	}
	return (hash & 0x7fffffff);
}

HashMap hash_map;

// don't check uniqueness, since this problem guarantee the uniqueness
void hash_insert(char* word, int value)
{
	size_t hv;
	HashMapNode *pnode = (HashMapNode*)malloc(sizeof(HashMapNode));
	hv = hash(word) % HASH_SIZE;
	pnode->next = hash_map.vec[hv];
	hash_map.vec[hv] = pnode;
	strcpy(pnode->word, word);
	pnode->word_len = strlen(word);
	pnode->idx = value;
	++hash_map.size;
}

bool hash_find(char* word, int* value)
{
	size_t hv;
	HashMapNode* pnode;
	hv = hash(word) % HASH_SIZE;
	pnode = hash_map.vec[hv];
	while(pnode != NULL)
	{
		if(strcmp(pnode->word, word) == 0)
		{
			*value = pnode->idx;
			return true;
		}
		pnode = pnode->next;
	}
	return false;
}

void hash_clear()
{
	hash_map.size = 0;
	for(int i = 0; i < HASH_SIZE; i++)
	{
		if(hash_map.vec[i] != NULL)
		{
			HashMapNode* pnode = hash_map.vec[i];
			do
			{
				HashMapNode* temp = pnode;
				pnode = pnode->next;
				free(temp);
			} while(pnode != NULL);
			hash_map.vec[i] = NULL;
		}
	}
}
//

int ncities;

struct Edge
{
	int source;
	int target;
	int depart_time;
	int arrive_time;
};

struct TrainSched
{
	Edge oedge[MAXV][MAXD];
	int nodegree[MAXV];	// out degree
	Edge iedge[MAXV][MAXD];
	int nidegree[MAXV];	// in degree
} train_sched;

int estime;	// earliest starting time
int scity, tcity;	// city idx
int dtime, atime;

int arrive_time[MAXV];	// used by the algorithm
int depart_time[MAXV];
bool visited[MAXV];
bool rvisited[MAXV];

bool find_optimal_path()
{
	int i, cur_city, cur_dtime, cur_atime;
	for(i = 0; i < ncities; i++)
	{
		arrive_time[i] = 2400;
		depart_time[i] = 0;
		visited[i] = false;
		rvisited[i] = false;
	}
	// find the earliest arrival time
	arrive_time[scity] = 0;
	while(1)
	{
		cur_city = -1;
		cur_atime = 2400;
		for(i = 0; i < ncities; i++)
		{
			if(!visited[i] && arrive_time[i] < cur_atime)
			{
				cur_city = i;
				cur_atime = arrive_time[i];
			}
		}
		if(cur_city == -1)
			return false;
		visited[cur_city] = true;
		if(cur_city == tcity)
		{
			atime = arrive_time[tcity];
			break;
		}
		for(i = 0; i < train_sched.nodegree[cur_city]; i++)
		{
			Edge &edge = train_sched.oedge[cur_city][i];
			if(visited[edge.target] || edge.depart_time < estime || edge.depart_time < arrive_time[cur_city] || arrive_time[edge.target] <= edge.arrive_time)
				continue;
			arrive_time[edge.target] = edge.arrive_time;
		}
	}
	// find the latest feasible departure time
	rvisited[tcity] = true;
	for(i = 0; i < train_sched.nidegree[tcity]; i++)
	{
		Edge &edge = train_sched.iedge[tcity][i];
		if(rvisited[edge.source] || edge.arrive_time != atime || edge.depart_time < estime)
			continue;
		if(depart_time[edge.source] < edge.depart_time)
			depart_time[edge.source] = edge.depart_time;
	}
	while(1)
	{
		cur_city = -1;
		cur_dtime = 0;
		for(i = 0; i < ncities; i++)
		{
			if(!rvisited[i] && depart_time[i] > cur_dtime)
			{
				cur_city = i;
				cur_dtime = depart_time[i];
			}
		}
		rvisited[cur_city] = true;
		if(cur_city == scity)
		{
			dtime = depart_time[scity];
			break;
		}
		for(i = 0; i < train_sched.nidegree[cur_city]; i++)
		{
			Edge &edge = train_sched.iedge[cur_city][i];
			if(rvisited[edge.source] || edge.depart_time < estime || edge.arrive_time > depart_time[cur_city] || depart_time[edge.source] >= edge.depart_time)
				continue;
			depart_time[edge.source] = edge.depart_time;
		}
	}
	return true;
}

int main()
{
	int i, j, t, k, ntrains, nstops;
	char city1[100], city2[100];
	scanf("%d", &t);
	for(k = 1; k <= t; k++)
	{
		scanf("%d", &ncities);
		if(k > 1)
			hash_clear();
		for(i = 0; i < ncities; i++)
		{
			scanf("%s", city1);
			hash_insert(city1, i);
			train_sched.nodegree[i] = train_sched.nidegree[i] = 0;
		}
		scanf("%d", &ntrains);
		for(i = 0; i < ntrains; i++)
		{
			scanf("%d", &nstops);
			scanf("%d%s", &dtime, city1);
			hash_find(city1, &scity);
			for(j = 1; j < nstops; j++)
			{
				scanf("%d%s", &atime, city2);
				hash_find(city2, &tcity);
				Edge &edge1 = train_sched.oedge[scity][train_sched.nodegree[scity]++];
				Edge &edge2 = train_sched.iedge[tcity][train_sched.nidegree[tcity]++];
				edge1.source = edge2.source = scity;
				edge1.target = edge2.target = tcity;
				edge1.depart_time = edge2.depart_time = dtime;
				edge1.arrive_time = edge2.arrive_time = atime;
				scity = tcity;
				dtime = atime;
			}
		}
		scanf("%d%s%s", &estime, city1, city2);
		hash_find(city1, &scity);
		hash_find(city2, &tcity);
		
		printf("Scenario %d\n", k);
		if(find_optimal_path())
			printf("Departure %04d %s\nArrival   %04d %s\n\n", dtime, city1, atime, city2);
		else
			printf("No connection\n\n");
	}
	return 0;
}
