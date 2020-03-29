#include <iostream>
#include <memory.h>

using namespace std;

int h[100];	// hartal indices
int last[100];	// last hartal time

int main()
{
	int i, j, t;
	int T, N, P;
	int count;
	bool hartal;
	cin>>T;
	for(t=0; t<T; t++)
	{
		cin>>N;
		cin>>P;
		for(i=0; i<P; i++)
		{
			cin>>h[i];
		}
		count = 0;
		memset(last, 0, sizeof(last));
		for(i=1; i<=N; i++)
		{
			hartal = false;
			for(j=0; j<P; j++)
			{
				if(i-last[j]==h[j])
				{
					hartal = true;
					last[j] = i;
				}
			}
			if(hartal && (i+1)%7!=0 && i%7!=0)
				count++;
		}
		cout<<count<<endl;
	}
	return 0;
}