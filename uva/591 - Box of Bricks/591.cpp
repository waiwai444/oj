#include <iostream>

using namespace std;

int main()
{
	int i, n;
	int c = 0;
	int *box;
	int s, t;
	while(1)
	{
		cin>>n;
		if(n==0)
			break;
		c++;
		t = 0;
		box = new int[n];
		for(i=0; i<n; i++)
		{
			cin>>box[i];
			t += box[i];
		}
		t = t/n;
		s = 0;
		for(i=0; i<n; i++)
		{
			if(box[i]-t>0)
				s += box[i]-t;
		}
		cout<<"Set #"<<c<<endl;
		cout<<"The minimum number of moves is "<<s<<'.'<<endl<<endl;
	}
	return 0;
}