#include <stdio.h>
#include <math.h>

#define INF ((unsigned int)-1)
#define EPS 1e-9

int n;
int tree[5000][3];
char grid[256][256][256];
int bin[10];

int main()
{
	int i, j, k, l, x, y, z;
	n = 0;
	while(scanf("%d%d%d", &x, &y, &z), x || y || z)
	{
		tree[n][0] = x;
		tree[n][1] = y;
		tree[n][2] = z;
		n++;
		if(grid[x][y][z])
			grid[x][y][z] = 2;
		else
			grid[x][y][z] = 1;
	}
	for(i = 0; i < n; i++)
	{
		if(grid[tree[i][0]][tree[i][1]][tree[i][2]] == 2)
		{
			bin[0]++;
			continue;
		}
		int back = tree[i][0]-9 >= 0 ? tree[i][0]-9 : 0;
		int front = tree[i][0]+9 < 256 ? tree[i][0]+9 : 255;
		int left = tree[i][1]-9 >= 0 ? tree[i][1]-9 : 0;
		int right = tree[i][1]+9 < 256 ? tree[i][1]+9 : 255;
		int bottom = tree[i][2]-9 >= 0 ? tree[i][2]-9 : 0;
		int top = tree[i][2]+9 < 256 ? tree[i][2]+9 : 255;
		unsigned int min_dist = INF;
		for(j = back; j <= front; j++)
			for(k = left; k <= right; k++)
				for(l = bottom; l <= top; l++)
					if((j != tree[i][0] || k != tree[i][1] || l != tree[i][2]) && grid[j][k][l])
					{
						unsigned int dist = (unsigned int)sqrt((double)(tree[i][0]-j)*(tree[i][0]-j)+(tree[i][1]-k)*(tree[i][1]-k)+(tree[i][2]-l)*(tree[i][2]-l)+EPS);
						if(dist < min_dist)
						{
							min_dist = dist;
							if(min_dist == 1)
								goto finished;
						}
					}
		finished:
		if(min_dist < 10)
			bin[min_dist]++;
	}
	for(i = 0; i < 10; i++)
		printf("%4d", bin[i]);
	printf("\n");
	return 0;
}
