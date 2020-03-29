#include <stdio.h>

int dptable[301][301];

int main()
{
	int i, j, k, m, n, s, t;
	for(i = 2; i <= 300; i++)
	{
		dptable[1][i] = dptable[1][i-1]+1;
		dptable[i][1] = dptable[i-1][1]+1;
	}
	for(i = 2; i <= 300; i++)
	{
		for(j = 2; j <= 300; j++)
		{
			s = dptable[i][1]+dptable[i][j-1]+1;
			/*for(k = 2; k <= j/2; k++)
				if((t = dptable[i][k]+dptable[i][j-k]+1) < s)
					s = t;
			for(k = 1; k <= i/2; k++)
				if((t = dptable[k][j]+dptable[i-k][j]+1) < s)
					s = t;*/
			dptable[i][j] = s;
		}
	}
	while(scanf("%d%d", &m, &n) != EOF)
		printf("%d\n", dptable[m][n]);
	return 0;
}