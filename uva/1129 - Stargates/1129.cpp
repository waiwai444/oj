#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 6000000

int n;
int repr[MAXN+1];

int find(int x)
{
	return x == repr[x] ? x : repr[x] = find(repr[x]);
}

void union_set(int x, int y)
{
	int rx = find(x), ry = find(y);
	if(rx == ry)
		return;
	repr[ry] = rx;
}

int main()
{
	int i, src, dst, nnn, dststep, srcstep;
	char buf[100], *p;
	while(fgets(buf, sizeof(buf), stdin))
	{
		if(buf[0] == 'D' || buf[0] == 'd')
		{
			n = atoi(strtok(buf+1, " "));
			for(i = 1; i <= n; i++)
				repr[i] = i;
		}
		else if(buf[0] == 'C' || buf[0] == 'c' || buf[0] == 'Q' || buf[0] == 'q')
		{
			src = atoi(strtok(buf+1, " "));
			dst = atoi(strtok(NULL, " "));
			p = strtok(NULL, " ");
			nnn = p ? atoi(p) : 1;
			p = strtok(NULL, " ");
			dststep = p ? atoi(p) : 1;
			p = strtok(NULL, " ");
			srcstep = p ? atoi(p) : 0;
		}

		if(buf[0] == 'C' || buf[0] == 'c')
		{
			for(i = 0; i < nnn; i++)
				union_set(src+i*srcstep, dst+i*dststep);
		}
		else if(buf[0] == 'Q' || buf[0] == 'q')
		{
			int c = 0, d = 0, rx, ry;
			for(i = 0; i < nnn; i++)
			{
				rx = find(src+i*srcstep);
				ry = find(dst+i*dststep);
				if(rx == ry)
					++c;
				else
					++d;
			}
			printf("%d - %d\n", c, d);
		}
	}
	return 0;
}

