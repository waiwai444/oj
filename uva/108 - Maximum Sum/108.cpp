#include <stdio.h>

int n;
int matrix[101][101];
int col_sum[101][101];

int main()
{
	int i, j, k;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			scanf("%d", &matrix[i][j]);
	for(j = 1; j <= n; j++)
		for(i = 1; i <= n; i++)
			col_sum[i][j] = col_sum[i-1][j]+matrix[i][j];
	int max_size = -128, size;
	for(i = 1; i <= n; i++)
		for(j = i; j <= n; j++)
		{
			size = 0;
			for(k = 1; k <= n; k++)
			{
				size += col_sum[j][k]-col_sum[i-1][k];
				if(size > max_size)
					max_size = size;
				if(size < 0)
					size = 0;
			}
		}
	printf("%d\n", max_size);
	return 0;
}
