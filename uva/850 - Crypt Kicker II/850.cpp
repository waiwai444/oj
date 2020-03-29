#include <iostream>
#include <cstring>

using namespace std;

char plain_text[] = {"the quick brown fox jumps over the lazy dog"};
char cipher[100][81];
int cipher_num;
char map[26];

int decrypt_plain_text()
{
	int i, j;
	int plain_text_len = strlen(plain_text);
	for(i=0; i<cipher_num; i++)
	{
		if(plain_text_len!=strlen(cipher[i]))
			continue;
		memset(map, 0, sizeof(map));
		for(j=0; j<plain_text_len; j++)
		{
			if(cipher[i][j]==' ')
			{
				if(plain_text[j]==' ')
					continue;
				break;
			}
			if(map[cipher[i][j]-'a']==0)
				map[cipher[i][j]-'a'] = plain_text[j];
			else if(map[cipher[i][j]-'a']!=plain_text[j])
				break;
		}
		if(j==plain_text_len)
			return i;
	}
	return -1;
}

int main()
{
	int i, j, k, l;
	int data_set_num;
	char line[81];
	cin>>data_set_num;
	cin.getline(line, 81);
	cin.getline(line, 81);
	while(data_set_num-->0)
	{
		cipher_num = 0;
		cin.getline(line, 81);
		while(line[0]!=0)
		{
			strcpy(cipher[cipher_num++], line);
			cin.getline(line, 81);
		}
		
		if((k=decrypt_plain_text())!=-1)
		{
			for(i=0; i<cipher_num; i++)
			{
				if(i==k)
					cout<<plain_text<<endl;
				else
				{
					l = strlen(cipher[i]);
					for(j=0; j<l; j++)
					{
						if(cipher[i][j]==' ')
							cout<<' ';
						else
							cout<<map[cipher[i][j]-'a'];
					}
					cout<<endl;
				}
			}
		}
		else
			cout<<"No solution."<<endl;
		if(data_set_num>0)
			cout<<endl;
	}
	return 0;
}