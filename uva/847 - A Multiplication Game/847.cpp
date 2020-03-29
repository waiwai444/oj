#include <iostream>

using namespace std;

int main()
{
	long long n;
	while(cin>>n)
	{
		while(true)
		{
			if(n%9==0)
				n /= 9;
			else
				n = n/9+1;
			if(n==1)
			{
				cout<<"Stan wins."<<endl;
				break;
			}
			if(n%2==0)
				n /= 2;
			else
				n = n/2+1;
			if(n==1)
			{
				cout<<"Ollie wins."<<endl;
				break;
			}
		}
	}
	return 0;
}