#include <cstdio>

#define NMAX 14

int permutation[NMAX][NMAX][NMAX];

int main()
{
	int t, n, p, r;
	permutation[1][1][1] = 1;
	for(int i=2; i<NMAX; i++)
		for(int j=1; j<=i; j++)
			for(int k=1; k<=i; k++)
				permutation[i][j][k] = permutation[i-1][j-1][k]+permutation[i-1][j][k-1]+(i-2)*permutation[i-1][j][k];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d", &n, &p, &r);
		printf("%d\n", permutation[n][p][r]);
	}
	return 0;
}