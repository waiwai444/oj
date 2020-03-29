#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class UBigInteger {
	char digit[200];
	int lastdigit;
	
public:
	UBigInteger();
	UBigInteger(const UBigInteger &x);
	inline void operator =(string num);
	inline bool operator ==(unsigned int x);
	inline bool operator ==(const UBigInteger &x);
	inline bool operator <(const UBigInteger &x);
	inline bool operator <=(const UBigInteger &x);
	inline bool operator >(const UBigInteger &x);
	inline bool operator >=(const UBigInteger &x);
	inline UBigInteger operator +(const UBigInteger &x);
	inline void clear();
};

UBigInteger::UBigInteger()
{
	clear();
}

UBigInteger::UBigInteger(const UBigInteger &x)
{
	clear();
	lastdigit = x.lastdigit;
	for(int i=0; i<=lastdigit; i++)
		digit[i] = x.digit[i];
}

inline void UBigInteger::clear()
{
	for(int i=0; i<200; i++)
		digit[i] = 0;
	lastdigit = -1;
}

inline void UBigInteger::operator =(string num)
{
	int i, j;
	j = 0;
	clear();
	for(i=num.length()-1; i>=0; i--)
		digit[j++] = num[i]-'0';
	lastdigit = j-1;
}

inline bool UBigInteger::operator ==(unsigned int x)
{
	int i;
	if(lastdigit<0)
		return false;
	else if(lastdigit==0 && digit[0]==x)
		return true;
	for(i=0; i<=lastdigit; i++)
	{
		if(x%10!=digit[i])
			return false;
		x /= 10;
	}
	if(x>0)
		return false;
	return true;
}

inline bool UBigInteger::operator ==(const UBigInteger &x)
{
	int i;
	if(lastdigit!=x.lastdigit)
		return false;
	for(i=0; i<=lastdigit; i++)
		if(digit[i]!=x.digit[i])
			return false;
	return true;
}

inline bool UBigInteger::operator <(const UBigInteger &x)
{
	int i;
	if(lastdigit<x.lastdigit)
		return true;
	else if(lastdigit>x.lastdigit)
		return false;
	for(i=lastdigit; i>=0; i--)
		if(digit[i]<x.digit[i])
			return true;
		else if(digit[i]>x.digit[i])
			return false;
	return false;
}

inline bool UBigInteger::operator <=(const UBigInteger &x)
{
	return *this<x || *this==x;
}

inline bool UBigInteger::operator >(const UBigInteger &x)
{
	int i;
	if(lastdigit<x.lastdigit)
		return false;
	else if(lastdigit>x.lastdigit)
		return true;
	for(i=lastdigit; i>=0; i--)
		if(digit[i]<x.digit[i])
			return false;
		else if(digit[i]>x.digit[i])
			return true;
	return false;
}

inline bool UBigInteger::operator >=(const UBigInteger &x)
{
	return *this>x || *this==x;
}

inline UBigInteger UBigInteger::operator +(const UBigInteger &x)
{
	UBigInteger result;
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

UBigInteger fibs[500];

int binary_search(UBigInteger x)
{
	int high, low, mid;
	low = 0;
	high = 499;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(fibs[mid]==x)
			return mid;
		if(fibs[mid]<x)
			low = mid+1;
		else
			high = mid-1;
	}
	return low;
}

int main()
{
	int i, j;
	string num;
	UBigInteger a, b;
	UBigInteger f1, f2, tmp;
	fibs[0] = "1";
	fibs[1] = "2";
	for(i=2; i<500; i++)
		fibs[i] = fibs[i-1]+fibs[i-2];
	while(true)
	{
		cin>>num;
		a = num;
		cin>>num;
		b = num;
		if(a==0 && b==0)
			break;
		i = binary_search(a);
		j = binary_search(b);
		if(fibs[j]>b)
			j--;
		cout<<j-i+1<<endl;
	}
	return 0;
}