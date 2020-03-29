
#include <iostream>

using namespace std;

int main()
{
	int n;
	int len;
	int ones;
	while(cin>>n)
	{
		ones = 1%n;
		len = 1;
		while(ones!=0)
		{
			ones = (10*ones+1)%n;
			len++;
		}
		cout<<len<<endl;
	}
	return 0;
}