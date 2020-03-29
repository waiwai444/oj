#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> shells;
int orig_order[200];

int main()
{
	int i, j, k, n;
	string str;
	cin>>k;
	shells.reserve(200);
	while(k-->0)
	{
		cin>>n;
		getline(cin, str);
		shells.resize(n);
		for(i=0; i<n; i++)
			getline(cin, shells[i]);
		for(i=0; i<n; i++)
		{
			getline(cin, str);
			for(j=0; j<n; j++)
			{
				if(str==shells[j])
				{
					orig_order[i] = j;
					break;
				}
			}
		}
		for(i=n-2; i>=0; i--)
			if(orig_order[i]>orig_order[i+1])
				break;
		for(; i>=0; i--)
			cout<<shells[orig_order[i]]<<endl;
		cout<<endl;
		if(k>0)
			shells.clear();
	}
	return 0;
}