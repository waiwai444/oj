#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

inline void flip(vector<int> &flapjack)
{
	int i, j, k;
	int t;
	if(flapjack.size()==1)
	{
		return;
	}
	for(i=flapjack.size()-1; i>0; i--)
	{
		k = i;
		for(j=i-1; j>=0; j--)
			if(flapjack[k]<flapjack[j])
				k = j;
		if(k==i)
			continue;
		for(j=0; j<(k+1)/2; j++)
		{
			t = flapjack[j];
			flapjack[j] = flapjack[k-j];
			flapjack[k-j] = t;
		}
		for(j=0; j<(i+1)/2; j++)
		{
			t = flapjack[j];
			flapjack[j] = flapjack[i-j];
			flapjack[i-j] = t;
		}
		if(k!=0)
			cout<<flapjack.size()-k<<' ';
		cout<<flapjack.size()-i<<' ';
	}
}

int main()
{
	int i;
	vector<int> flapjack;
	flapjack.reserve(30);
	char line[256];
	char *temp;
	while(cin.getline(line, 256))
	{
		if(line[0]==0)
			continue;
		cout<<line<<endl;
		flapjack.push_back(atoi(strtok(line, " ")));
		while((temp=strtok(NULL, " "))!=NULL)
			flapjack.push_back(atoi(temp));
		
		flip(flapjack);
		cout<<0<<endl;

		flapjack.clear();
	}
	return 0;
}