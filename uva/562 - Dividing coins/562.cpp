#include <stdio.h>
#include <string.h>

#define MAX 25000

int m;
int psum[MAX+1], p;
bool flag[MAX+1];

int main()
{
	int i, j, tc, v, q, tot;
	scanf("%d", &tc);
	psum[0] = 0;
	while(tc--)
	{
		scanf("%d", &m);
		p = 1;
		memset(flag, false, sizeof(flag));
		flag[0] = true;
		tot = 0;
		for(i = 0; i < m; i++)
		{
			scanf("%d", &v);
			tot += v;
			q = p;
			for(j = 0; j < p; j++)
			{
				if(psum[j]+v <= MAX && !flag[psum[j]+v])
				{
					psum[q++] = psum[j]+v;
					flag[psum[j]+v] = true;
				}
			}
			p = q;
		}
		for(i = tot/2; i >= 0; i--)
		{
			if(flag[i])
			{
				printf("%d\n", tot-i-i);
				break;
			}
		}
	}
	return 0;
}
