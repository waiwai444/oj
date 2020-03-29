#include <cstdio>
#include <cmath>

inline int digit_sum(int n)
{
	int sum = 0; 
	while(n>0)
	{
		sum += n%10;
		n /= 10;
	}
	return sum;
}

inline int prime_factor_sum(int n)
{
	int sum = 0;
	int c = n;
	while(c%2==0)
	{
		sum += 2;
		c /= 2;
	}
	int i = 3;
	int tmp = sqrt((long double)c)+1;
	while(i<=tmp)
	{
		if(c%i==0)
		{
			if(i<10)
				sum += i;
			else
				sum += digit_sum(i);
			c /= i;
			tmp = sqrt((long double)c)+1;
		}
		else
			i += 2;
	}
	if(2==n || c==n)
		return 0;	// a prime number is not considered as a Smith number
	if(c>1)
		sum += digit_sum(c);
	return sum;
}

int main()
{
	int n, s, s1, s2;
	int d;
	scanf("%d", &d);
	while(d-->0)
	{
		scanf("%d", &n);
		for(s=n+1;; s++)
		{
			s1 = prime_factor_sum(s);
			s2 = digit_sum(s);
			if(s1==s2)
				break;
		}
		printf("%d\n", s);
	}
	return 0;
}