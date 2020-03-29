#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int comp(const void *a, const void *b)
{
	return (int)(*(char *)a-*(char *)b);
}

int main()
{
	int i;
	char cipher[101];
	char text[101];
	char cipher_count[26];
	char text_count[26];
	bool flag;
	while(true)
	{
		cin.getline(cipher, 101);
		if(cipher[0]==0)
			break;
		cin.getline(text, 101);
		memset(cipher_count, 0, 26*sizeof(char));
		memset(text_count, 0, 26*sizeof(char));
		for(i=0; i<100&cipher[i]!=0; i++)
		{
			cipher_count[cipher[i]-'A']++;
			text_count[text[i]-'A']++;
		}
		qsort(cipher_count, 26, sizeof(char), comp);
		qsort(text_count, 26, sizeof(char), comp);
		flag = true;
		for(i=0; i<26; i++)
		{
			if(cipher_count[i]!=text_count[i])
			{
				flag = false;
				break;
			}
		}
		if(flag==true)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}