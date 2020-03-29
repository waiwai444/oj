#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int i, j, l1, l2;
	char a[1001], b[1001];
	int c1[26];
	int c2[26];
	while(cin.getline(a, 1001))
	{
		cin.getline(b, 1001);
		memset(c1, 0, sizeof(c1));
		memset(c2, 0, sizeof(c2));
		l1 = strlen(a);
		l2 = strlen(b);
		for(i=0; i<l1; i++)
			c1[a[i]-'a']++;
		for(i=0; i<l2; i++)
			c2[b[i]-'a']++;
		for(i=0; i<26; i++)
		{
			if(c1[i]>0 && c2[i]>0)
			{
				for(j=0; j<c1[i] && j<c2[i]; j++)
				{
					cout<<char('a'+i);
				}
			}
		}
		cout<<endl;
	}
	return 0;
}