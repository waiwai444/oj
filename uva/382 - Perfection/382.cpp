#include <iostream>

using namespace std;

int main()
{
	int i, num, sum;
	cout<<"PERFECTION OUTPUT"<<endl;
	while(cin>>num && num)
	{
		cout.width(5);
		cout<<num<<"  ";
		if(num==1)
			sum = 0;
		else
		{
			sum = 1;
			for(i=2; i*i<num; i++)
				if(num%i==0)
					sum += (i+num/i);
			if(i*i==num)
				sum += i;
		}
		if(sum==num)
			cout<<"PERFECT"<<endl;
		else if(sum<num)
			cout<<"DEFICIENT"<<endl;
		else
			cout<<"ABUNDANT"<<endl;
	}
	cout<<"END OF OUTPUT"<<endl;
	return 0;
}