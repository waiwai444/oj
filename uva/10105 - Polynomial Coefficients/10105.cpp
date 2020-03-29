#include <iostream>

using namespace std;

int combination(int n, int m)
{
	int i;
	long double c;
	if(m==0 || n==m)
		return 1;
	c = 1;
	if(m>n-m)
		m = n-m;
	for(i=n; i>n-m; i--)
		c = c*i/(i-n+m);
	return (int)c;
}

int main()
{
	int i, n, k, ni, r;
	while(cin>>n>>k)
	{
		r = 1;
		for(i=0; i<k; i++)
		{
			cin>>ni;
			if(ni>0)
			{
				r *= combination(n, ni);
				n -= ni;
			}
		}
		cout<<r<<endl;
	}
	return 0;
}