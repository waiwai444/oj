#include <iostream>
#include <cmath>

using namespace std;

inline int round(long double x)	// 0.5 is rounded down here!
{
	int n = x;
	if(n+0.5<x)
		n++;
	return n;
}

int main()
{
	int i, j, k, n, x, y, dist;
	long double tmp;
	cin>>n;
	for(i=0; i<n; i++)
	{
		cin>>x>>y;
		dist = y-x;
		if(dist==0)
		{
			cout<<0<<endl;
			continue;
		}
		tmp = sqrt(1+4*(long double)dist)/2;
		k = round(tmp);
		j = dist-k*(k-1);
		if(j<=k)
			cout<<2*k-1<<endl;
		else
			cout<<2*k<<endl;
	}
	return 0;
}