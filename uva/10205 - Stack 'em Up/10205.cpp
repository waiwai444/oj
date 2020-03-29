// WA experience: there is no blank line after the output of the last set of data! (different from poj2469)
#include <iostream>
#include <stdlib.h>

using namespace std;

int shuffleMethod[100][52];

int main()
{
	int s;
	int i, j, k, t;
	int n;
	char line[256];
	char stack[52];
	char temp[52];
	cin>>s;
	for(t=0; t<s; t++)
	{
		cin>>n;
		for(i=0; i<52; i++)
			stack[i] = i;
		for(i=0; i<n; i++)	// get shuffle methods
		{
			for(j=0; j<52; j++)
			{
				cin>>shuffleMethod[i][j];
			}
		}
		cin.getline(line, 256);
		while(cin.getline(line, 256))	// shuffle
		{
			if(line[0]==0)
				break;
			k = atoi(line)-1;
			for(i=0; i<52; i++)
				temp[i] = stack[shuffleMethod[k][i]-1];
			for(i=0; i<52; i++)
				stack[i] = temp[i];
		}
		int suit;
		int value;
		for(i=0; i<52; i++)	// output
		{
			value = stack[i]%13;
			suit = stack[i]/13;
			if(value>=0 && value<=8)
				cout<<value+2;
			else
			{
				switch(value)
				{
				case 9:
					cout<<"Jack";
					break;
				case 10:
					cout<<"Queen";
					break;
				case 11:
					cout<<"King";
					break;
				case 12:
					cout<<"Ace";
					break;
				}
			}
			cout<<" of ";
			switch(suit)
			{
			case 0:
				cout<<"Clubs";
				break;
			case 1:
				cout<<"Diamonds";
				break;
			case 2:
				cout<<"Hearts";
				break;
			case 3:
				cout<<"Spades";
				break;
			}
			cout<<endl;
		}
		if(t<s-1)
			cout<<endl;
	}
	return 0;
}