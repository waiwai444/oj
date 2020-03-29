#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	int i, j, k, l, n, s, tmp;
	int psum[64];
	bool flag[64];
	int total_sum;
	int unknown[10];
	while(cin>>n)
	{
		s = n*(n-1)/2;
		total_sum = 0;
		for(i=0; i<s; i++)
		{
			cin>>psum[i];
			total_sum += psum[i];
		}
		if(total_sum%(n-1)!=0)
		{
			cout<<"Impossible"<<endl;
			continue;
		}
		sort(&psum[0], &psum[s]);
		flag[0] = flag[1] = true;
		for(i=2; i<n; i++)	// enumerate the value of x2+x3
		{
			for(j=2; j<s; j++)
				flag[j] = false;
			tmp = psum[0]+psum[1]-psum[i];
			if(tmp%2!=0)
				continue;
			unknown[0] = tmp/2;
			tmp = psum[0]-psum[1]+psum[i];
			if(tmp%2!=0)
				continue;
			unknown[1] = tmp/2;
			tmp = psum[1]-psum[0]+psum[i];
			if(tmp%2!=0)
				continue;
			unknown[2] = tmp/2;
			flag[i] = true;
			for(j=3; j<n; j++)	// find the values of x4, ..., xn
			{
				for(k=2; k<s; k++)
					if(!flag[k])
						break;
				unknown[j] = psum[k]-unknown[0];
				if(unknown[j]<unknown[j-1])	// it may happen only when finding x4
					break;
				flag[k] = true;
				l = 1;
				for(k=k+1; k<s; k++)
				{
					if(flag[k])
						continue;
					if(l==j)
						break;
					if(unknown[l]+unknown[j]==psum[k])
					{
						flag[k] = true;
						l++;
					}
				}
				if(l<j)
					break;
			}
			if(j==n)
				break;
		}
		if(i==n)
			cout<<"Impossible"<<endl;
		else
			for(j=0; j<n; j++)
			{
				cout<<unknown[j];
				if(j<n-1)
					cout<<' ';
				else
					cout<<endl;
			}
	}
	return 0;
}