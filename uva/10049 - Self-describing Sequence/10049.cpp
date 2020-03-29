#include <cstdio>

#define N 1000000

int f[N];

int main()
{
	f[1] = 1, f[2] = f[3] = 2;
	int i, j, t;
	i = 4;
	t = 3;
	while(i<=N)
	{
		for(j=0; j<f[t]; j++)
		{
			f[i] = t;
			if(++i>N)
				break;
		}
		t++;
	}
	int n;
	while(scanf("%d", &n)!=EOF)
	{
		if(n==0)
			break;
		if(n<=N)
			printf("%d\n", f[n]);
		else
		{
			i = 0, j = 0;
			while(i<n)
				i += f[++j];
			printf("%d\n", j);
		}
	}
	return 0;
}