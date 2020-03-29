#include <iostream>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b, long long &x, long long &y)
{
	if(b==0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long x1, y1;
	long long d = gcd(b, a%b, x1, y1);
	x = y1;
	y = x1-a/b*y1;
	return d;
}

int main()
{
	long long n, c1, c2, n1, n2, x1, x2, d, k1, k2;
	while(cin>>n)
	{
		if(n==0)
			break;
		cin>>c1>>n1>>c2>>n2;
		d = gcd(n1, n2, x1, x2);
		if(n%d!=0)
		{
			cout<<"failed"<<endl;
			continue;
		}
		x1 *= n/d;
		x2 *= n/d;
		k1 = ceil(-x2*d/(double)n1);
		k2 = floor(x1*d/(double)n2);
		if(k1>k2)
		{
			cout<<"failed"<<endl;
			continue;
		}
		if(c2*n1>c1*n2)
		{
			x2 = x2+k1*n1/d;
			x1 = (n-n2*x2)/n1;
			cout<<x1<<' '<<x2<<endl;
		}
		else
		{
			x1 = x1-k2*n2/d;
			x2 = (n-n1*x1)/n2;
			cout<<x1<<' '<<x2<<endl;
		}
	}
	return 0;
}