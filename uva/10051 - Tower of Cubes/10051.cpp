
#include <stdio.h>
#include <set>

struct Cube
{
	int faces[6];
};

int N;
Cube cube_set[501];

std::set<int> color_idx[101];

int max_height[501][6];	// for 6 up faces each cube
int upper_cube[501][6];
int upper_cube_top_face[501][6];
int max_height_cube_idx;
int max_height_face_idx;

int main()
{
	int test_case = 0;
	int i, j, k;
	Cube cube;
	int result_cube_idx[500];
	int result_face_idx[500];
	int height;
	while(scanf("%d", &N))
	{
		if(N == 0)
			break;
		++test_case;
		for(i = 1; i <= 100; i++)
			color_idx[i].clear();
		
		scanf("%d %d %d %d %d %d", &cube.faces[0], &cube.faces[1], &cube.faces[2], &cube.faces[3], &cube.faces[4], &cube.faces[5]);
		for(j = 0; j < 6; j++)
		{
			max_height[1][j] = 1;
			upper_cube[1][j] = -1;
			upper_cube_top_face[1][j] = -1;
		}
		cube_set[1] = cube;
		for(j = 0; j < 6; j++)
			color_idx[cube.faces[j]].insert(1);
		max_height_cube_idx = 1;
		max_height_face_idx = 0;
		for(i = 2; i <= N; i++)
		{
			scanf("%d %d %d %d %d %d", &cube.faces[0], &cube.faces[1], &cube.faces[2], &cube.faces[3], &cube.faces[4], &cube.faces[5]);
			for(j = 0; j < 6; j++)
			{
				max_height[i][j] = 1;
				upper_cube[i][j] = -1;
				upper_cube_top_face[1][j] = -1;
				for(std::set<int>::const_iterator it = color_idx[cube.faces[j]].begin(); it != color_idx[cube.faces[j]].end(); ++it)
				{
					for(k = 0; k < 6; k++)
					{
						int top_face;
						if((k & 1) == 0)
							top_face = k + 1;
						else
							top_face = k - 1;
						if(cube_set[*it].faces[k] == cube.faces[j] && max_height[*it][top_face] >= max_height[i][j])
						{
							max_height[i][j] = max_height[*it][top_face] + 1;
							upper_cube[i][j] = *it;
							upper_cube_top_face[i][j] = top_face;
						}
					}
				}
				if(max_height[i][j] > max_height[max_height_cube_idx][max_height_face_idx])
				{
					max_height_cube_idx = i;
					max_height_face_idx = j;
				}
			}
			cube_set[i] = cube;
			for(j = 0; j < 6; j++)
				color_idx[cube.faces[j]].insert(i);
		}
		
		i = max_height_cube_idx;
		j = max_height_face_idx;
		height = 0;
		while(1)
		{
			result_cube_idx[height] = i;
			result_face_idx[height] = j;
			++height;
			if(upper_cube[i][j] == -1)
				break;
			int tmp_i = upper_cube[i][j];
			j = upper_cube_top_face[i][j];
			i = tmp_i;
		}
		
		if(test_case > 1)
			printf("\n");
		printf("Case #%d\n%d\n", test_case, height);
		for(i = height - 1; i >= 0; i--)
		{
			printf("%d ", result_cube_idx[i]);
			switch(result_face_idx[i])
			{
				case 0:
					printf("front\n");
					break;
				case 1:
					printf("back\n");
					break;
				case 2:
					printf("left\n");
					break;
				case 3:
					printf("right\n");
					break;
				case 4:
					printf("top\n");
					break;
				case 5:
					printf("bottom\n");
					break;
			}
		}
	}
	return 0;
}
