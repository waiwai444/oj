#include <iostream>
#include <math.h>

using namespace std;

int loopLen[3000000];
int stack[3000000];

int main()
{
	int i, j;
	int k, n;
	long long l;
	int stackSize;
	int max;
	loopLen[1] = 1;
	for(k=1; k<=21; k++)
	{
		loopLen[(int)pow((float)2, k)] = k+1;
	}
	while(cin>>i>>j)
	{
		max = 0;
		cout<<i<<' '<<j<<' ';
		if(i>j)
			k = i, i = j, j = k;
		for(n=i; n<=j; n++)
		{
			l = n;
			stackSize = 0;
			while(l<3000000 && loopLen[l]==0 || l>=3000000)
			{
				stack[stackSize++] = l;
				if(l%2==0)
					l /= 2;
				else
					l = 3*l+1;
			}
			for(k=stackSize-1; k>=0; k--)
			{
				if(stack[k]<3000000 && stack[k]>0)
					loopLen[stack[k]] = loopLen[l]+stackSize-k;
			}
			if(loopLen[n]>max)
				max = loopLen[n];
		}
		cout<<max<<endl;
	}
	return 0;
}