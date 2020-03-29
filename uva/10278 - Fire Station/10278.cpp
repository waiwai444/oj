
#include <stdio.h>
#include <string.h>

#define MAXV 500
#define MAXDIST 0x3f3f3f3f

int dist_map[MAXV + 1][MAXV + 1];
int nvertices;
bool fire_station[MAXV + 1];
int dist_to_fire_station[MAXV + 1];

void floyd()
{
	int i, j, k;
	for(k = 1; k <= nvertices; k++)
		for(i = 1; i <= nvertices; i++)
			for(j = 1; j <= nvertices; j++)
			{
				int temp = dist_map[i][k] + dist_map[k][j];
				if(temp < dist_map[i][j])
					dist_map[i][j] = dist_map[j][i] = temp;
			}
}

void find_dist_to_fire_station()
{
	int i, j;
	for(i = 1; i <= nvertices; i++)
	{
		dist_to_fire_station[i] = MAXDIST;
		for(j = 1; j <= nvertices; j++)
			if(fire_station[j] && dist_to_fire_station[i] > dist_map[i][j])
				dist_to_fire_station[i] = dist_map[i][j];
	}
}

int find_new_fire_station()
{
	int i, j;
	int result = 1;
	int min, max;
	min = MAXDIST;
	for(i = 1; i <= nvertices; i++)
	{
		max = 0;
		for(j = 1; j <= nvertices; j++)
		{
			if(dist_to_fire_station[j] >= dist_map[j][i] && max < dist_map[j][i])
				max = dist_map[j][i];
			else if(dist_to_fire_station[j] < dist_map[j][i] && max < dist_to_fire_station[j])
				max = dist_to_fire_station[j];
		}
		if(max < min)
		{
			min = max;
			result = i;
		}
	}
	return result;
}

int main()
{
	int i, t, f, v, w, dist;
	char line[100];
	scanf("%d", &t);
	fgets(line, sizeof(line), stdin);
	while(t-- > 0)
	{
		scanf("%d%d", &f, &nvertices);
		memset(fire_station, false, sizeof(fire_station));
		for(i = 0; i < f; i++)
		{
			scanf("%d", &v);
			fire_station[v] = true;
		}
		memset(dist_map, MAXDIST, sizeof(dist_map));
		for(i = 1; i <= nvertices; i++)
			dist_map[i][i] = 0;
		fgets(line, sizeof(line), stdin);
		while(fgets(line, sizeof(line), stdin) && line[0] != '\n')
		{
			sscanf(line, "%d %d %d", &v, &w, &dist);
			dist_map[v][w] = dist_map[w][v] = dist;
		}
		floyd();
		find_dist_to_fire_station();
		printf("%d\n", find_new_fire_station());
		if(t > 0)
			printf("\n");
	}
	return 0;
}
