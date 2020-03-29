#include <stdio.h>
#include <string.h>

int dp[4096][16][16];
int ans[4096];

inline int encode_cfg(int c[])
{
	return c[0]+(c[1]<<3)+(c[2]<<6)+(c[3]<<9);
}

int decode_cfg(int cfg, int c[])
{
	c[0] = cfg&7;
	c[1] = (cfg&56)>>3;
	c[2] = (cfg&448)>>6;
	c[3] = (cfg&3584)>>9;
	int n = 0;
	if(c[0]) ++n;
	if(c[1]) ++n;
	if(c[2]) ++n;
	if(c[3]) ++n;
	return n;
}

inline int encode_pos(int col, int num)
{
	return (col<<2)+num;
}

inline void decode_pos(int pos, int *col, int *num)
{
	*col = pos>>2;
	*num = pos&3;
}

void solve()
{
	int i, i2, j, k, l, c[4], d[4], u1, v1, u2, v2, u3, v3;
	ans[0] = 1;
	for(i = 1; i < 4096; i++)
	{
		if(decode_cfg(i, c) == 1)
		{
			for(j = 0; j < 4; j++) if(c[j]) break;
			if(c[j] <= 3)
			{
				k = encode_pos(j, c[j]);
				ans[i] = dp[i][k][k] = 1;
			}
			continue;
		}
		for(j = 0; j < 16; j++)
		{
			decode_pos(j, &u1, &v1);
			if(v1 == 0 || c[u1] < v1)
				continue;
			for(k = 0; k < 16; k++)
			{
				decode_pos(k, &u2, &v2);
				if(v2 == 0 || c[u2] < v2)
					continue;
				memcpy(d, c, sizeof(d));
				d[u2] -= v2;
				i2 = encode_cfg(d);
				for(l = 0; l < 16; l++)
				{
					decode_pos(l, &u3, &v3);
					if(u2 == u3 || v2 == v3 || v3 == 0 || d[u3] < v3)
						continue;
					dp[i][j][k] += dp[i2][j][l];
				}
				if(u1 != u2 && v1 != v2)
					ans[i] += dp[i][j][k];
			}
		}
	}
}

int main()
{
	int i, tc, n, c[4], cfg;
	solve();
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &c[i]);
		for(; i < 4; i++)
			c[i] = 0;
		cfg = encode_cfg(c);
		printf("%d\n", ans[cfg]);
	}
	return 0;
}

