#include <stdio.h>

unsigned int N, L, U;

void solve()
{
	int pos = 31;
	unsigned int mask = 1<<31;
	
	while(pos >= 0 && (U & mask) == 0)
	{
		--pos;
		mask >>= 1;
	}
	
	unsigned int result = 0;	
	while(pos >= 0)
	{
		if((N & mask) == 0 && (result | mask) <= U || (result | mask-1) < L)
		{
			result |= mask;
		}
		--pos;
		mask >>= 1;
	}
	
	printf("%u\n", result);
}

int main()
{
	while(scanf("%u%u%u", &N, &L, &U) != EOF)
	{
		solve();
	}
	return 0;
}
