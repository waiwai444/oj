#include <iostream>
#include <memory.h>

using namespace std;

int seq[3000];
int diff[3000];

int main()
{
	int i;
	int n;
	int t;
	while(cin>>n)
	{
		if(n<=0)
			break;
		for(i=0; i<n; i++)
		{
			cin>>seq[i];
		}
		if(n==1)
		{
			cout<<"Jolly"<<endl;
			continue;
		}
		memset(diff, 0, sizeof(diff));
		for(i=0; i<n-1; i++)
		{
			t = seq[i]-seq[i+1];
			if(t<0)
				t = -t;
			if(t==0 || t>=n)
			{
				cout<<"Not jolly"<<endl;
				break;
			}
			if(diff[t]>0)
			{
				cout<<"Not jolly"<<endl;
				break;
			}
			else
			{
				diff[t] = 1;
			}
		}
		if(i==n-1)
			cout<<"Jolly"<<endl;
	}
	return 0;
}