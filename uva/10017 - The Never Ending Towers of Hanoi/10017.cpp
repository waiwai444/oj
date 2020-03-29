#include <cstdio>

#define MAXN 250

int n, m;
int peg[3][MAXN], h[3];
const char peg_name[3] = { 'A', 'B', 'C' };

void print()
{
	int i, j;
	for(i = 0; i < 3; i++)
	{
		printf("%c=>", peg_name[i]);
		if(h[i] > 0)
		{
			printf("  ");
			for(j = 0; j < h[i]; j++)
				printf(" %d", peg[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void solve()
{
	int i, j, k, l, d;
	d = (n&1) ? -1 : 1;
	for(i = 0; i < n; i++)
		peg[0][i] = n-i;
	h[0] = n, h[1] = h[2] = 0;
	print();
	for(i = j = 0; i < m; i += 2)
	{
		k = (j+d+3)%3;;
		peg[k][h[k]++] = peg[j][--h[j]];
		print();
		if(i+1 == m)
			break;
		l = 3-j-k;
		if(h[j] == 0 || (h[l] > 0 && peg[j][h[j]-1] > peg[l][h[l]-1]))
			peg[j][h[j]++] = peg[l][--h[l]];
		else
			peg[l][h[l]++] = peg[j][--h[j]];
		print();
		j = k;
	}
}

int main()
{
	int c = 0;
	while(scanf("%d%d", &n, &m), n)
	{
		printf("Problem #%d\n\n", ++c);
		solve();
	}
	return 0;
}

