#include <cstdio>
#include <cmath>

inline bool is_prime(int n)
{
	if(n>2 && n%2==0 || n==1)
		return false;
	int tmp = sqrt((double)n)+1;
	for(int i=3; i<=tmp; i+=2)
		if(n%i==0)
			return false;
	return true;
}

int main()
{
	int i, j;
	unsigned int a, n, s, t;
	while(scanf("%u", &n)!=EOF)
	{
		if(n==0)
			break;
		if(is_prime(n))
		{
			printf("%u is normal.\n", n);
			continue;
		}
		for(a=2; a<n; a++)
		{
			s = 1;
			t = a;
			i = 0;
			j = 1;
			while(i+j<n)
			{
				if(i+j*2<=n)
				{
					t = t*t%n;
					j <<= 1;
				}
				else
				{
					i += j;
					j = 1;
					s = s*t%n;
					t = a;
				}
			}
			s = s*t%n;
			if(s!=a)
				break;
		}
		if(a!=n)
			printf("%u is normal.\n", n);
		else
			printf("The number %u is a Carmichael number.\n", n);
	}
	return 0;
}