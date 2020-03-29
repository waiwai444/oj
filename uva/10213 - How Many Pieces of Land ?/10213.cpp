#include <iostream>

using namespace std;

#define MAXDIGIT 100

class BigInt {
	char digit[MAXDIGIT];
	int lastdigit;
	int sign;

	void shift(int offset);
	bool iszero() const;
public:
	BigInt();
	BigInt(int x);
	void clear();
	BigInt operator =(int x);
	BigInt operator -() const;
	BigInt operator +(const BigInt &x) const;
	BigInt operator -(const BigInt &x) const;
	BigInt operator *(const BigInt &x) const;
	BigInt operator /(const BigInt &x) const;
	bool operator >=(const BigInt &x) const;
	bool operator <(const BigInt &x) const;
	void print() const;
};

BigInt::BigInt()
{
	clear();
}

BigInt::BigInt(int x)
{
	int i;
	clear();
	if(x<0)
	{
		sign = -1;
		x = -x;
	}
	else
		sign = 1;
	if(x<10)
	{
		digit[0] = x;
		lastdigit = 0;
	}
	else
	{
		i = 0;
		while(x>0)
		{
			digit[i++] = x%10;
			x /= 10;
		}
		lastdigit = i-1;
	}
}

inline void BigInt::clear()
{
	for(int i=0; i<MAXDIGIT; i++)
		digit[i] = 0;
	lastdigit = -1;
	sign = 1;
}

inline void BigInt::print() const
{
	int i;
	if(sign==-1)
		cout<<'-';
	for(i=lastdigit; i>=0; i--)
		cout<<char(digit[i]+'0');
}

inline bool BigInt::iszero() const
{
	return lastdigit==0 && digit[0]==0;
}

inline BigInt BigInt::operator =(int x)
{
	*this = BigInt(x);
	return *this;
}

inline BigInt BigInt::operator -() const
{
	BigInt result;
	result = *this;
	result.sign = -result.sign;
	return result;
}

BigInt BigInt::operator +(const BigInt &x) const
{
	if(sign==1 && x.sign==-1)
		return (*this)-(-x);
	else if(sign==-1 && x.sign==1)
		return x-(-*this);
	int i, l;
	int carry;
	BigInt result;
	l = lastdigit>x.lastdigit?lastdigit:x.lastdigit;
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
	result.digit[i] = carry;
	if(carry==0)
		result.lastdigit = i-1;
	else
		result.lastdigit = i;
	if(sign==1)
		result.sign = 1;
	else
		result.sign = -1;
	return result;
}

BigInt BigInt::operator -(const BigInt &x) const
{
	if(sign==-1 && x.sign==1)
		return -((-*this)+x);
	else if(sign==1 && x.sign==-1)
		return *this+(-x);
	int i;
	int borrow = 0;
	BigInt result;
	if(sign==1)
	{
		if(*this>=x)
		{
			result.lastdigit = 0;
			for(i=0; i<=lastdigit; i++)
			{
				result.digit[i] = digit[i]-x.digit[i]-borrow;
				if(result.digit[i]<0)
				{
					result.digit[i] += 10;
					borrow = 1;
				}
				else
					borrow = 0;
				if(result.digit[i]!=0)
					result.lastdigit = i;
			}
			if(result.lastdigit==-1)
				result.lastdigit = 0;
		}
		else
			return -(x-*this);
	}
	else if(sign==-1)
	{
		if(x>=*this)
			return -((-*this)-(-x));
		else
			return -x-(-*this);
	}
	return result;
}

inline void BigInt::shift(int offset)
{
	int i;
	if(offset>0)
	{
		for(i=lastdigit; i>=0; i--)
			digit[i+offset] = digit[i];
		for(i=offset-1; i>=0; i--)
			digit[i] = 0;
		lastdigit += offset;
	}
	else if(offset<0)
	{
		offset = -offset;
		for(i=offset; i<=lastdigit; i++)
			digit[i-offset] = digit[i];
		for(i=lastdigit-offset+1; i<=lastdigit; i++)
			digit[i] = 0;
		lastdigit -= offset;
	}
}

inline BigInt BigInt::operator *(const BigInt &x) const
{
	int i, j;
	BigInt result;
	if(iszero() || x.iszero())
	{
		result.lastdigit = 0;
		return result;
	}
	BigInt tmp = *this;
	tmp.sign = 1;
	for(i=0; i<=x.lastdigit; i++)
	{
		for(j=1; j<=x.digit[i]; j++)
			result = result+tmp;
		tmp.shift(1);
	}
	result.lastdigit = lastdigit+x.lastdigit;
	if(result.digit[result.lastdigit+1]!=0)
		result.lastdigit++;
	result.sign = sign*x.sign;
	return result;
}

inline BigInt BigInt::operator /(const BigInt &x) const
{
	int i;
	BigInt result;
	BigInt tmp1, tmp2;
	tmp1 = *this;
	tmp2 = x;
	tmp1.sign = tmp2.sign = 1;
	if(tmp1<tmp2)
	{
		result.lastdigit = 0;
		return result;
	}
	BigInt rem;
	for(i=lastdigit; i>=0; i--)
	{
		if(rem.lastdigit!=0 || rem.digit[0]!=0)
			rem.shift(1);
		rem.digit[0] = digit[i];
		if(rem<tmp2)
			continue;
		if(result.lastdigit==-1)
			result.lastdigit = i;
		while(rem>=tmp2)
		{
			rem = rem-tmp2;
			result.digit[i]++;
		}
	}

	result.sign = sign*x.sign;
	return result;
}

inline bool BigInt::operator >=(const BigInt &x) const
{
	if(sign>x.sign)
		return true;
	else if(sign<x.sign)
		return false;
	if(lastdigit>x.lastdigit)
		return sign==1?true:false;
	else if(lastdigit<x.lastdigit)
		return sign==1?false:true;
	int i;
	for(i=lastdigit; i>=0; i--)
	{
		if(digit[i]<x.digit[i])
			return sign==1?false:true;
		else if(digit[i]>x.digit[i])
			return sign==1?true:false;
	}
	return sign==1?true:false;
}

inline bool BigInt::operator <(const BigInt &x) const
{
	return !(*this>=x);
}

int main()
{
	int i, n, s;
	BigInt bi;
	cin>>s;
	for(i=0; i<s; i++)
	{
		cin>>n;
		bi = n;
		bi = bi*(bi-1)*(bi*bi-bi*5+18)/24+1;
		bi.print();
		cout<<endl;
		bi.clear();
	}
	return 0;
}