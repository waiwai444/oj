#include <stdio.h>
#include <string.h>

int n;
char matrix[25][26];
int rec[25][25];	// the number of 1's in rectangle ((0,0),(i,j))

int main()
{
	int i, j, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s", matrix[0]);
		n = strlen(matrix[0]);
		for(i = 1; i < n; i++)
			scanf("%s", matrix[i]);
		memset(rec, 0, sizeof(rec));
		
		rec[0][0] = matrix[0][0]-'0';
		for(i = 1; i < n; i++)
		{
			rec[0][i] = rec[0][i-1]+matrix[0][i]-'0';
			rec[i][0] = rec[i-1][0]+matrix[i][0]-'0';
		}
		for(i = 1; i < n; i++)
			for(j = 1; j < n; j++)
				rec[i][j] = rec[i][j-1]+rec[i-1][j]-rec[i-1][j-1]+matrix[i][j]-'0';
		
		int max_size = 0;
		int r1, r2, c1, c2;
		for(r1 = 0; r1 < n; r1++)
		{
			for(r2 = r1; r2 < n; r2++)
			{
				for(c1 = 0; c1 < n; c1++)
				{
					for(c2 = c1; c2 < n; c2++)
					{
						int size = (c2-c1+1)*(r2-r1+1);
						if(size <= max_size)
							continue;
						int ones;
						if(r1 == 0 && c1 == 0)
							ones = rec[r2][c2];
						else if(r1 == 0)
							ones = rec[r2][c2]-rec[r2][c1-1];
						else if(c1 == 0)
							ones = rec[r2][c2]-rec[r1-1][c2];
						else
							ones = rec[r2][c2]-rec[r1-1][c2]-rec[r2][c1-1]+rec[r1-1][c1-1];
						if(ones == size && size > max_size)
							max_size = size;
					}
				}
			}
		}
		printf("%d\n", max_size);
		if(tc > 0)
			printf("\n");
	}
	return 0;
}
