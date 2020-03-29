#include <iostream>

using namespace std;

char table[100][100];
char result[100][100];

int main()
{
	int i, j;
	int n, m;
	int num = 0;
	while(cin>>n>>m)
	{
		if(n==0 || m==0)
			break;
		for(i=0; i<n; i++)
		{
			for(j=0; j<m; j++)
			{
				cin>>table[i][j];
				if(table[i][j]=='*')
					result[i][j] = '*';
				else
					result[i][j] = '0';
			}
		}
		for(i=0; i<n; i++)
		{
			for(j=0; j<m; j++)
			{
				if(table[i][j]=='.')
					continue;
				if(i>0)
				{
					if(table[i-1][j]!='*')
						result[i-1][j] += 1;
					if(j>0 && table[i-1][j-1]!='*')
						result[i-1][j-1] += 1;
					if(j<m-1 && table[i-1][j+1]!='*')
						result[i-1][j+1] += 1;
				}
				if(i<n-1)
				{
					if(table[i+1][j]!='*')
						result[i+1][j] += 1;
					if(j>0 && table[i+1][j-1]!='*')
						result[i+1][j-1] += 1;
					if(j<m-1 && table[i+1][j+1]!='*')
						result[i+1][j+1] += 1;
				}
				if(j>0 && table[i][j-1]!='*')
					result[i][j-1] += 1;
				if(j<m-1 && table[i][j+1]!='*')
					result[i][j+1] += 1;
			}
		}
		if(num>0)
			cout<<"\nField #"<<++num<<":"<<endl;
		else
			cout<<"Field #"<<++num<<":"<<endl;
		for(i=0; i<n; i++)
		{
			for(j=0; j<m; j++)
			{
				cout<<result[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}