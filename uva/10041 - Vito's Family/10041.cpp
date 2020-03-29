#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	int i, d, r, v;
	int s[500];
	int dist;
	cin>>d;
	while(d-->0)
	{
		cin>>r;
		for(i=0; i<r; i++)
			cin>>s[i];
		if(r%2==0)
		{
			nth_element(s, s+r/2-1, s+r);
			v = s[r/2-1];
		}
		else
		{
			nth_element(s, s+r/2, s+r);
			v = s[r/2];
		}
		dist = 0;
		for(i=0; i<r; i++)
			if(s[i]<v)
				dist += v-s[i];
			else if(s[i]>v)
				dist += s[i]-v;
		cout<<dist<<endl;
	}
	return 0;
}