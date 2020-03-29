#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int m, n, k;
char matrix[64][64];
char word[32][64];

bool check(int r, int c, int w, int l)
{
	int i;
	if(n-c>=l)
	{
		for(i=1; i<l; i++)
		{
			if(word[w][i]!=matrix[r][c+i])
				break;
		}
		if(i==l)
			return true;
		if(r+1>=l)
		{
			for(i=1; i<l; i++)
			{
				if(word[w][i]!=matrix[r-i][c+i])
					break;
			}
			if(i==l)
				return true;
		}
		if(m-r>=l)
		{
			for(i=1; i<l; i++)
			{
				if(word[w][i]!=matrix[r+i][c+i])
					break;
			}
			if(i==l)
				return true;
		}
	}
	if(r+1>=l)
	{
		for(i=1; i<l; i++)
			if(word[w][i]!=matrix[r-i][c])
				break;
		if(i==l)
			return true;
	}
	if(m-r>=l)
	{
		for(i=1; i<l; i++)
			if(word[w][i]!=matrix[r+i][c])
				break;
		if(i==l)
			return true;
	}
	if(c+1>=l)
	{
		for(i=1; i<l; i++)
			if(word[w][i]!=matrix[r][c-i])
				break;
		if(i==l)
			return true;
		if(r+1>=l)
		{
			for(i=1; i<l; i++)
			{
				if(word[w][i]!=matrix[r-i][c-i])
					break;
			}
			if(i==l)
				return true;
		}
		if(m-r>=l)
		{
			for(i=1; i<l; i++)
			{
				if(word[w][i]!=matrix[r+i][c-i])
					break;
			}
			if(i==l)
				return true;
		}
	}
	return false;
}

int main()
{
	int i, j, l, w;
	int testDataNum;
	char line[64];
	cin>>testDataNum;
	cin.getline(line, 64);
	while(testDataNum-->0)
	{
		cin.getline(line, 64);
		cin>>m>>n;
		cin.getline(line, 64);
		for(i=0; i<m; i++)
		{
			cin.getline(line, 64);
			strcpy(matrix[i], line);
			for(j=0; j<n; j++)
			{
				if(matrix[i][j]>='A' && matrix[i][j]<='Z')
					matrix[i][j] = tolower(matrix[i][j]);
			}
		}
		cin>>k;
		cin.getline(line, 64);
		for(i=0; i<k; i++)
		{
			cin.getline(line, 64);
			strcpy(word[i], line);
			for(j=0; j<n && word[i][j]!='\0'; j++)
			{
				if(word[i][j]>='A' && word[i][j]<='Z')
					word[i][j] = tolower(word[i][j]);
			}
		}

		for(w=0; w<k; w++)
		{
			l = strlen(word[w]);
			for(i=0; i<m; i++)
			{
				for(j=0; j<n; j++)
				{
					if(matrix[i][j]!=word[w][0])
						continue;
					if(check(i, j, w, l))
					{
						cout<<i+1<<' '<<j+1;
						goto next;
					}
				}
			}
next:
			cout<<endl;
		}
		if(testDataNum>0)
			cout<<endl;
	}
	return 0;
}