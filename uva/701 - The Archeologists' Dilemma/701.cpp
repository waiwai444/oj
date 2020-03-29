#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	int k;
	long long n;
	long long tmp;
	int digit;
	long double b1, b2;
	while(cin>>n)
	{
		digit = 0;
		tmp = n;
		while(tmp>0)
		{
			digit++;
			tmp /= 10;
		}
		k = digit+1;
		while(true)
		{
			b1 = (log10l(n+1)+k)/log10l(2);
			b2 = (log10l(n)+k)/log10l(2);
			if(b1>ceill(b2))
			{
				cout<<int(ceill(b2))<<endl;
				break;
			}
			k++;
		}
	}
	return 0;
}