#include <stdio.h>
#include <limits.h>

int nc, nt;
unsigned int tkn[50], tbl, res_l, res_u;

unsigned int lcm_tbl[50][50][50][50];

unsigned int gcd(unsigned int x, unsigned int y)
{
	return y == 0 ? x : gcd(y, x%y);
}

unsigned int lcm(unsigned int x, unsigned int y)
{
	return x/gcd(x,y)*y;
}

void get_all_lcm()
{
	int i, j, k, l;
	unsigned int l1, l2;
	for(i = 0; i < nc; i++)
	{
		for(j = i+1; j < nc; j++)
		{
			l1 = lcm(tkn[i], tkn[j]);
			for(k = j+1; k < nc; k++)
			{
				l2 = lcm(l1, tkn[k]);
				for(l = k+1; l < nc; l++)
				{
					lcm_tbl[i][j][k][l] = lcm(l2, tkn[l]);
				}
			}
		}
	}
}

void solve()
{
	int i, j, k, l;
	unsigned int tl, tu, m;
	res_l = 0;
	res_u = UINT_MAX;
	for(i = 0; i < nc; i++)
	{
		for(j = i+1; j < nc; j++)
		{
			for(k = j+1; k < nc; k++)
			{
				for(l = k+1; l < nc; l++)
				{
					m = lcm_tbl[i][j][k][l];
					tl = tbl/m*m;
					if(tl == tbl)
					{
						res_l = res_u = tl;
						return;
					}
					tu = tl+m;
					if(tl > res_l)
						res_l = tl;
					if(tu < res_u)
						res_u = tu;
				}
			}
		}
	}
}

int main()
{
	int i;
	while(scanf("%d%d", &nc, &nt), nc)
	{
		for(i = 0; i < nc; i++)
			scanf("%d", &tkn[i]);
		get_all_lcm();
		for(i = 0; i < nt; i++)
		{
			scanf("%d", &tbl);
			solve();
			printf("%u %u\n", res_l, res_u);
		}
	}
	return 0;
}
