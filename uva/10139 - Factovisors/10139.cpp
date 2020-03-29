#include <iostream>
#include <cmath>
#include <list>

using namespace std;

list<int> & prime_factorize(int n, list<int> & factors)
{
	if(n==0)
		return factors;
	while((n&1)==0)
	{
		factors.push_back(2);
		n >>= 1;
	}
	int b = sqrt((double)n)+1;
	for(int i=3; i<=b; i+=2)
	{
		while(n%i==0)
		{
			factors.push_back(i);
			n /= i;
			b = sqrt((double)n)+1;
		}
	}
	if(n>1)
		factors.push_back(n);
	return factors;
}

int main()
{
	int i;
	int m, n, t;
	while(cin>>n>>m)
	{
		if(n>=m && m!=0)
		{
			cout<<m<<" divides "<<n<<"!"<<endl;
			continue;
		}
		else if(m==0)
		{
			cout<<m<<" does not divide "<<n<<"!"<<endl;
			continue;
		}
		list<int> factors_m;
		prime_factorize(m, factors_m);
		for(i=2; i<=n;)
		{
			t = i;
			for(list<int>::iterator j=factors_m.begin(); j!=factors_m.end();)
			{
				if(t%(*j)==0)
				{
					t /= (*j);
					j = factors_m.erase(j);
					if(t==1)
						break;
				}
				else
					j++;
			}
			if(factors_m.size()==0)
				break;
			if(factors_m.front()>i+1)
				i = factors_m.front();
			else
				i++;
		}
		if(factors_m.size()==0)
			cout<<m<<" divides "<<n<<"!"<<endl;
		else
			cout<<m<<" does not divide "<<n<<"!"<<endl;
	}
	return 0;
}