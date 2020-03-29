#include <stdio.h>

int n, m;
int pow2[20];

struct matrix_t
{
	int v[2][2];
} ans, base;

void init()
{
	pow2[0] = 1;
	for(int i = 1; i < 20; i++)
		pow2[i] = pow2[i-1]*2;
}

void init_case()
{
	ans.v[0][0] = ans.v[1][1] = 1;
	ans.v[0][1] = ans.v[1][0] = 0;
	base.v[0][0] = base.v[0][1] = base.v[1][0] = 1;
	base.v[1][1] = 0;
}

void multiply(matrix_t &a, const matrix_t &b)
{
	matrix_t tmp;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			tmp.v[i][j] = ((long long)a.v[i][0]*b.v[0][j]+(long long)a.v[i][1]*b.v[1][j])%pow2[m];
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			a.v[i][j] = tmp.v[i][j];
}

int solve()
{
	if(m == 0 || n == 0)
		return 0;
	if(n == 1)
		return 1;
	int p = n-1;
	init_case();
	while(p)
	{
		if(p&1)
			multiply(ans, base);
		multiply(base, base);
		p >>= 1;
	}
	return ans.v[0][0];
}

int main()
{
	init();
	while(scanf("%d%d", &n, &m) != EOF)
	{
		printf("%d\n", solve());
	}
	return 0;
}

