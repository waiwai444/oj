#include <stdio.h>

bool flag[1000001];

int digits_sum(int n)
{
	int sum = 0;
	while(n > 0)
	{
		sum += n%10;
		n /= 10;
	}
	return sum;
}

int main()
{
	int n, dn;
	for(n = 1; n <= 1000000; n++)
	{
		dn = n+digits_sum(n);
		if(dn <= 1000000)
			flag[dn] = true;
	}
	for(n = 1; n <= 1000000; n++)
		if(!flag[n])
			printf("%d\n", n);
	return 0;
}