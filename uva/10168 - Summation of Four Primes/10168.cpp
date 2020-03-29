#include <iostream>

using namespace std;

#define MAXNUM 10000000

bool is_prime[MAXNUM+1];

inline void get_prime()	// Eratosthenes sieve
{
	int i, j;
	is_prime[0] = is_prime[1] = false;
	is_prime[2] = true;
	for(i=3; i<=MAXNUM; i++)
	{
		if((i&1)==0)
			is_prime[i] = false;
		else
			is_prime[i] = true;
	}
	for(i=3; i<=MAXNUM; i+=2)
	{
		if(!is_prime[i])
			continue;
		j=2;
		while(i*j<=MAXNUM)
			is_prime[i*(j++)] = false;
	}
}

int main()
{
	int i, n;
	get_prime();
	while(cin>>n)
	{
		if(n<8)
		{
			cout<<"Impossible."<<endl;
			continue;
		}
		if((n&1)==0)
		{
			cout<<"2 2 ";
			n -= 4;
		}
		else
		{
			cout<<"2 3 ";
			n -= 5;
		}
		if(n==4)
		{
			cout<<"2 2"<<endl;
			continue;
		}
		for(i=3; i<=MAXNUM; i+=2)
		{
			if(!is_prime[i])
				continue;
			if(is_prime[n-i])
			{
				cout<<i<<' '<<n-i<<endl;
				break;
			}
		}
	}
	return 0;
}