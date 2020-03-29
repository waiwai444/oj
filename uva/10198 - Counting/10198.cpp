#include <iostream>

using namespace std;

class UBigInt {
	const static int MAXDIGIT = 500;
	char digit[MAXDIGIT];
	int lastdigit;
	
public:
	UBigInt();
	UBigInt(unsigned int x);
	UBigInt operator =(unsigned int x);
	UBigInt operator +(const UBigInt &x) const;
	void clear();
	void print() const;
};

UBigInt::UBigInt()
{
	clear();
}

UBigInt::UBigInt(unsigned int x)
{
	clear();
	if(x<10)
	{
		digit[0] = x;
		lastdigit = 0;
		return;
	}
	while(x>0)
	{
		digit[++lastdigit] = x%10;
		x /= 10;
	}
}

inline void UBigInt::clear()
{
	for(int i=0; i<MAXDIGIT; i++)
		digit[i] = 0;
	lastdigit = -1;
}

inline UBigInt UBigInt::operator =(unsigned int x)
{
	*this = UBigInt(x);
	return *this;
}

inline UBigInt UBigInt::operator +(const UBigInt &x) const
{
	UBigInt result;
	int carry;
	int i;
	int l = x.lastdigit>lastdigit?x.lastdigit:lastdigit;
	carry = 0;
	for(i=0; i<=l; i++)
	{
		result.digit[i] = digit[i]+x.digit[i]+carry;
		if(result.digit[i]>=10)
		{
			result.digit[i] -= 10;
			carry = 1;
		}
		else
			carry = 0;
	}
	if(carry==1)
	{
		result.digit[i] = 1;
		result.lastdigit = i;
	}
	else
		result.lastdigit = i-1;
	return result;
}

void UBigInt::print() const
{
	int i;
	for(i=lastdigit; i>=0; i--)
		cout<<char(digit[i]+'0');
}

UBigInt counting[1001];

int main()
{
	int i, n;
	counting[1] = 2;
	counting[2] = 5;
	counting[3] = 13;
	for(i=4; i<=1000; i++)
		counting[i] = counting[i-1]+counting[i-1]+counting[i-2]+counting[i-3];
	while(cin>>n)
	{
		counting[n].print();
		cout<<endl;
	}
	return 0;
}