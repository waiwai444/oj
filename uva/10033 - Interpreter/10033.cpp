#include <iostream>
#include <string.h>

using namespace std;

int reg[10];
char memory[1000][3];

int main()
{
	int i, pc;
	int count;
	int arg1, arg2;
	int temp;
	int n;
	char input[8];
	cin>>n;
	cin.getline(input, 8);
	cin.getline(input, 8);
	for(i=0; i<n; i++)
	{
		memset(reg, 0, sizeof(reg));
		memset(memory, '0', sizeof(memory));
		count = 0;
		while(cin.getline(input, 8))
		{
			if(input[0]==0)
				break;
			memory[count][0] = input[0];
			memory[count][1] = input[1];
			memory[count][2] = input[2];
			count++;
		}
		pc = 0;
		count = 0;
		while((memory[pc][0]!='1' || memory[pc][1]!='0' || memory[pc][2]!='0'))
		{
			count++;
			arg1 = memory[pc][1]-'0';
			arg2 = memory[pc][2]-'0';
			switch(memory[pc][0])
			{
			case '2':
				reg[arg1] = arg2;
				break;
			case '3':
				reg[arg1] = reg[arg1]+arg2;
				if(reg[arg1]>=1000)
					reg[arg1] -= 1000;
				break;
			case '4':
				reg[arg1] = reg[arg1]*arg2;
				if(reg[arg1]>=1000)
					reg[arg1] %= 1000;
				break;
			case '5':
				reg[arg1] = reg[arg2];
				break;
			case '6':
				reg[arg1] += reg[arg2];
				if(reg[arg1]>=1000)
					reg[arg1] -= 1000;
				break;
			case '7':
				reg[arg1] *= reg[arg2];
				if(reg[arg1]>=1000)
					reg[arg1] %= 1000;
				break;
			case '8':
				reg[arg1] = (memory[reg[arg2]][0]-'0')*100+(memory[reg[arg2]][1]-'0')*10+(memory[reg[arg2]][2]-'0');
				break;
			case '9':
				temp = reg[arg1];
				memory[reg[arg2]][2] = temp%10+'0';
				temp /= 10;
				memory[reg[arg2]][1] = temp%10+'0';
				temp /= 10;
				memory[reg[arg2]][0] = temp+'0';
				break;
			case '0':
				if(reg[arg2]!=0)
					pc = reg[arg1]-1;
				break;
			}
			pc++;
		}
		count++;
		cout<<count<<endl;
		if(i<n-1)
			cout<<endl;
	}
	return 0;
}
