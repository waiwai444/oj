#include <iostream>

using namespace std;

int main()
{
	int i, j, k;
	int s, n;
	char digit[10];
	int digitLen;
	while(cin>>s>>n)
	{
		if(s==0)
			break;
		digitLen = 0;
		if(n==0)
			digit[digitLen++] = 0;
		else
		{
			while(n!=0)
			{
				digit[digitLen++] = n%10;
				n /= 10;
			}
		}
		// print the first line
		for(i=digitLen-1; i>=0; i--)
		{
			switch(digit[i])
			{
			case 0: case 2: case 3: case 5: case 6: case 7: case 8: case 9:
				cout<<' ';
				for(j=0; j<s; j++)
					cout<<'-';
				cout<<' ';
				break;
			case 1: case 4:
				for(j=0; j<s+2; j++)
					cout<<' ';
				break;
			}
			if(i>0)
				cout<<' ';
			else
				cout<<endl;
		}
		// print the upper part
		for(k=0; k<s; k++)
		{
			for(i=digitLen-1; i>=0; i--)
			{
				switch(digit[i])
				{
				case 0: case 4: case 8: case 9:
					cout<<'|';
					for(j=0; j<s; j++)
						cout<<' ';
					cout<<'|';
					break;
				case 1: case 2: case 3: case 7:
					for(j=0; j<s+1; j++)
						cout<<' ';
					cout<<'|';
					break;
				case 5: case 6:
					cout<<'|';
					for(j=0; j<s+1; j++)
						cout<<' ';
					break;
				}
				if(i>0)
					cout<<' ';
				else
					cout<<endl;
			}
		}
		// print the middle line
		for(i=digitLen-1; i>=0; i--)
		{
			switch(digit[i])
			{
			case 0: case 1: case 7:
				for(j=0; j<s+2; j++)
					cout<<' ';
				break;
			case 2: case 3: case 4: case 5: case 6: case 8: case 9:
				cout<<' ';
				for(j=0; j<s; j++)
					cout<<'-';
				cout<<' ';
				break;
			}
			if(i>0)
				cout<<' ';
			else
				cout<<endl;
		}
		// print the lower part
		for(k=0; k<s; k++)
		{
			for(i=digitLen-1; i>=0; i--)
			{
				switch(digit[i])
				{
				case 0: case 6: case 8:
					cout<<'|';
					for(j=0; j<s; j++)
						cout<<' ';
					cout<<'|';
					break;
				case 1: case 3: case 4: case 5: case 7: case 9:
					for(j=0; j<s+1; j++)
						cout<<' ';
					cout<<'|';
					break;
				case 2:
					cout<<'|';
					for(j=0; j<s+1; j++)
						cout<<' ';
					break;
				}
				if(i>0)
					cout<<' ';
				else
					cout<<endl;
			}
		}
		// print the bottom line
		for(i=digitLen-1; i>=0; i--)
		{
			switch(digit[i])
			{
			case 0: case 2: case 3: case 5: case 6: case 8: case 9:
				cout<<' ';
				for(j=0; j<s; j++)
					cout<<'-';
				cout<<' ';
				break;
			case 1: case 4: case 7:
				for(j=0; j<s+2; j++)
					cout<<' ';
				break;
			}
			if(i>0)
				cout<<' ';
			else
				cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}