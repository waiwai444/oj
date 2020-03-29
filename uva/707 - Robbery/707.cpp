#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define NOT_FOUND 1
#define ESCAPED 2

bool pplace[100][101][101];	// possible places for each time
int w, h, t;
int robber_pos[100][2];

inline void init()
{
	for(int k = 0; k < t; k++)
	{
		for(int i = 1; i <= w; i++)
			for(int j = 1; j <= h; j++)
				pplace[k][i][j] = true;
		robber_pos[k][0] = robber_pos[k][1] = 0;
	}
}

inline void check(int i, int j, int k, int l)
{
	if(pplace[l][i][j] && !pplace[k][i][j] && (i == 1 || !pplace[k][i - 1][j]) && (i == w || !pplace[k][i + 1][j]) && (j == 1 || !pplace[k][i][j - 1]) && (j == h || !pplace[k][i][j + 1]))
		pplace[l][i][j] = false;
}

int traverse_backwards()
{
	int i, j, k, c;
	for(k = t - 1; k >= 0; k--)
	{
		c = 0;
		for(i = 1; i <= w; i++)
		{
			for(j = 1; j <= h; j++)
			{
				if(k != 0)
					check(i, j, k, k - 1);
				if(pplace[k][i][j])
					c++;
			}
		}
		if(c == 0)
			return ESCAPED;
	}
	return OK;
}

int traverse_forwards()
{
	int i, j, k, c, robber_x, robber_y, pre_x, pre_y, pre_time;
	bool found = false;
	pre_x = pre_y = 0;
	pre_time = -1;
	for(k = 0; k < t; k++)
	{
		c = robber_x = robber_y = 0;
		for(i = 1; i <= w; i++)
		{
			for(j = 1; j <= h; j++)
			{
				if(k != t - 1)
					check(i, j, k, k + 1);
				if(pplace[k][i][j] && c++ == 0)
				{
					robber_x = i;
					robber_y = j;
				}
			}
		}
		if(c == 1)
		{
			if(pre_time != -1)
			{
				if(pre_x == robber_x && k - pre_time == abs(robber_y - pre_y))
					while(++pre_time != k)
					{
						robber_pos[pre_time][0] = robber_x;
						robber_pos[pre_time][1] = ++pre_y;
					}
				else if(pre_y == robber_y && k - pre_time == abs(robber_x - pre_x))
					while(++pre_time != k)
					{
						robber_pos[pre_time][0] = ++pre_x;
						robber_pos[pre_time][1] = robber_y;
					}
			}
			robber_pos[k][0] = robber_x;
			robber_pos[k][1] = robber_y;
			pre_x = robber_x;
			pre_y = robber_y;
			pre_time = k;
			found = true;
		}
		else if(c == 0)
			return ESCAPED;
	}
	if(found)
		return OK;
	else
		return NOT_FOUND;
}

int main()
{
	int i, j, k, n, test_case = 0, result;
	int cur_t, left, top, right, bottom;
	while(scanf("%d%d%d", &w, &h, &t) != EOF && w)
	{
		init();
		scanf("%d", &n);
		for(k = 0; k < n; k++)
		{
			scanf("%d%d%d%d%d", &cur_t, &left, &top, &right, &bottom);
			cur_t--;
			for(i = left; i <= right; i++)
			{
				for(j = top; j <= bottom; j++)
				{
					pplace[cur_t][i][j] = false;
				}
			}
		}
		
		printf("Robbery #%d:\n", ++test_case);
		
		if(traverse_backwards() == ESCAPED)
			printf("The robber has escaped.\n");
		else
		{
			result = traverse_forwards();
			if(result == ESCAPED)
				printf("The robber has escaped.\n");
			else if(result == NOT_FOUND)
				printf("Nothing known.\n");
			else
			{
				for(k = 0; k < t; k++)
					if(robber_pos[k][0] != 0)
						printf("Time step %d: The robber has been at %d,%d.\n", k + 1, robber_pos[k][0], robber_pos[k][1]);
			}
		}
		printf("\n");
	}
	return 0;
}
