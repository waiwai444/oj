#include <iostream>

using namespace std;

inline long long reverse(long long x)
{
	if(x<10)
		return x;
	long long y = 0;
	while(x>0)
	{
		y = y*10+x%10;
		x /= 10;
	}
	return y;
}

int main()
{
	int i, n;
	int count;
	long long p;
	long long tmp;
	char sign;
	cin>>n;
	for(i=0; i<n; i++)
	{
		cin>>p;
		if(p<0)
		{
			p = -p;
			sign = '-';
		}
		else
			sign = 0;
		count = 0;
		while((tmp=reverse(p))!=p)
		{
			p += tmp;
			count++;
		}
		if(sign=='-')
			cout<<count<<" -"<<p<<endl;
		else
			cout<<count<<' '<<p<<endl;
	}
	return 0;
}