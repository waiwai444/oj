#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int i, k, l, r;
	int n, m;
	char answer_key[15000];
	char answer[15000];
	char line[128];
	char number1[15000];
	int number1_len;
	char number2[15000];
	int number2_len;
	bool pe, wa;
	r = 0;
	while(cin>>n)
	{
		if(n==0)
			break;
		r++;
		cin.getline(line, 128);
		answer_key[0] = 0;
		for(i=0; i<n; i++)
		{
			cin.getline(line, 128);
			strcat(answer_key, line);
			strcat(answer_key, "\n");
		}
		cin>>m;
		cin.getline(line, 128);
		answer[0] = 0;
		for(i=0; i<m; i++)
		{
			cin.getline(line, 128);
			strcat(answer, line);
			strcat(answer, "\n");
		}

		pe = wa = false;
		k = strlen(answer);
		l = strlen(answer_key);
		if(k==l)
		{
			for(i=0; i<k; i++)
				if(answer[i]!=answer_key[i])
					break;
			if(i==k)
			{
				cout<<"Run #"<<r<<": Accepted"<<endl;
				continue;
			}
		}
		number1_len = number2_len = 0;
		for(i=0; i<k; i++)
		{
			if(answer[i]>='0' && answer[i]<='9')
				number1[number1_len++] = answer[i];
		}
		number1[number1_len] = 0;
		for(i=0; i<l; i++)
		{
			if(answer_key[i]>='0' && answer_key[i]<='9')
				number2[number2_len++] = answer_key[i];
		}
		number2[number2_len] = 0;
		if(strcmp(number1, number2)==0)
			pe = true;
		else
			wa = true;

		if(wa)
			cout<<"Run #"<<r<<": Wrong Answer"<<endl;
		else if(pe)
			cout<<"Run #"<<r<<": Presentation Error"<<endl;
	}
	return 0;
}