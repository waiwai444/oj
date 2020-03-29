#include <iostream>
#include <iomanip>

using namespace std;

int pay[1000];

int main()
{
	int i, j;
	int n;
	int total;
	int avg;
	int exchange;
	int exchange2;
	char c[16];
	while(cin>>n)
	{
		if(n==0)
			break;
		total = 0;
		for(i=0; i<n; i++)
		{
			pay[i] = 0;
			cin>>c;
			j = 0;
			while(c[j]!=0)
			{
				if(c[j]!='.')
					pay[i] = pay[i]*10+(c[j]-'0');
				j++;
			}
			total += pay[i];
		}
		exchange = 0;
		avg = total/n;
		if(avg*n==total)
		{
			for(i=0; i<n; i++)
				if(pay[i]>avg)
					exchange += pay[i]-avg;
		}
		else
		{
			exchange2 = 0;
			for(i=0; i<n; i++)
				if(pay[i]>avg+1)
					exchange += pay[i]-avg-1;
			for(i=0; i<n; i++)
				if(pay[i]<avg)
					exchange2 += avg-pay[i];
			if(exchange2>exchange)
				exchange = exchange2;
		}
		cout<<"$"<<setiosflags(ios::fixed)<<setprecision(2)<<(double)exchange/100<<endl;
	}
	return 0;
}