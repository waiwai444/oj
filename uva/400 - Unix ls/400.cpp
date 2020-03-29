#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char filename[100][61];

int cmp_str(const void* s1, const void* s2)
{
	return strcmp((const char*)s1, (const char*)s2);
}

int main()
{
	int i, j, max_len;
	while(scanf("%d", &n) != EOF)
	{
		max_len = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%s", filename[i]);
			int len = strlen(filename[i]);
			if(len > max_len)
				max_len = len;
		}
		qsort(filename, n, sizeof(filename[0]), cmp_str);

		int ncols = max_len < 60 ? 61/(max_len+2) : 1;
		int nrows;
		if(n%ncols == 0)
			nrows = n/ncols;
		else
		{
			nrows = n/ncols+1;
			int last_row = n%ncols;
			while(ncols-1 > last_row)
			{
				if(ncols-1-last_row < nrows-1)
					last_row = ncols-1;
				else if(ncols-1-last_row == nrows-1)
				{
					last_row = ncols-1;
					ncols--;
				}
				else
				{
					last_row += nrows-1;
					ncols--;
				}
			}
		}

		printf("------------------------------------------------------------\n");
		for(i = 0; i < nrows; i++)
		{
			for(j = 0; j < ncols-1; j++)
			{
				printf("%-*s  ", max_len, filename[i+j*nrows]);
			}
			if(i+(ncols-1)*nrows < n)
				printf("%-*s \n", max_len, filename[i+(ncols-1)*nrows]);
			else
				printf("\n");
		}
	}
	return 0;
}