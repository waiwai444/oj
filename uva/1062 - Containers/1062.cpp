#include <cstdio>
#include <cstring>

char in[1001];

int solve()
{
	int i, j, l, s = 0;
	char c;
	l = strlen(in);
	for(i = l-1; i >= 0; --i)
	{
		if(!in[i])
			continue;
		++s;
		c = in[i];
		in[i] = 0;
		for(j = i-1; j >= 0; --j)
		{
			if(!in[j])
				continue;
			if(in[j] >= c)
			{
				c = in[j];
				in[j] = 0;
			}
		}
	}
	return s;
}

int main()
{
	int c = 0;
	while(scanf("%s", in), in[0] != 'e')
		printf("Case %d: %d\n", ++c, solve());
	return 0;
}

