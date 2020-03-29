#include <iostream>

using namespace std;

class UBigInt {
	const static int MAXDIGIT = 1500;
	const static int MOD = 1000000000;
	const static int WIDTH = 9;
	long long digit[MAXDIGIT];
	int lastdigit;

	void shift(int offset);
	void clear();
public:
	UBigInt();
	UBigInt(unsigned long long n);
	UBigInt operator =(unsigned long long n);
	UBigInt operator +(const UBigInt &n) const;
	UBigInt operator -(const UBigInt &n) const;
	UBigInt operator *(const UBigInt &n) const;
	UBigInt operator /(const UBigInt &n) const;
	bool operator >=(const UBigInt &n) const;
	bool operator <=(const UBigInt &n) const;
	bool operator >(const UBigInt &n) const;
	bool operator <(const UBigInt &n) const;
	void print() const;
};

inline void UBigInt::clear()
{
	for(int i=0; i<MAXDIGIT; i++)
		digit[i] = 0;
	lastdigit = -1;
}

inline void UBigInt::shift(int offset)
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

UBigInt::UBigInt()
{
	clear();
}

UBigInt::UBigInt(unsigned long long n)
{
	clear();
	if(n<MOD)
	{
		digit[0] = n;
		lastdigit = 0;
		return;
	}
	while(n>0)
	{
		digit[++lastdigit] = n%MOD;
		n /= MOD;
	}
}

inline UBigInt UBigInt::operator =(unsigned long long n)
{
	*this = UBigInt(n);
	return *this;
}

UBigInt UBigInt::operator +(const UBigInt &n) const
{
	int i;
	int l = lastdigit>=n.lastdigit?lastdigit:n.lastdigit;
	long long carry = 0;
	UBigInt result;
	for(i=0; i<=l; i++)
	{
		result.digit[i] = digit[i]+n.digit[i]+carry;
		if(result.digit[i]>=MOD)
		{
			result.digit[i] -= MOD;
			carry = 1;
		}
		else
			carry = 0;
	}
	if(carry==1)
	{
		result.digit[i] = carry;
		result.lastdigit = i;
	}
	else
		result.lastdigit = i-1;
	return result;
}

UBigInt UBigInt::operator -(const UBigInt &n) const
{
	int i;
	long long borrow = 0;
	UBigInt result;
	result.lastdigit = 0;
	for(i=0; i<=lastdigit; i++)
	{
		result.digit[i] = digit[i]-n.digit[i]-borrow;
		if(result.digit[i]<0)
		{
			result.digit[i] += MOD;
			borrow = 1;
		}
		else
			borrow = 0;
		if(result.digit[i]!=0)
			result.lastdigit = i;
	}
	return result;
}

UBigInt UBigInt::operator *(const UBigInt &n) const
{
	int i, j;
	long long carry = 0;
	UBigInt result;
	for(i=0; i<=n.lastdigit; i++)
	{
		for(j=0; j<=lastdigit; j++)
		{
			result.digit[i+j] += digit[j]*n.digit[i]+carry;
			if(result.digit[i+j]>=MOD)
			{
				carry = result.digit[i+j]/MOD;
				result.digit[i+j] %= MOD;
			}
			else
				carry = 0;
		}
		if(carry>0)
		{
			result.digit[i+j] = carry;
			result.lastdigit = i+j;
			carry = 0;
		}
		else
			result.lastdigit = i+j-1;
	}
	return result;
}

UBigInt UBigInt::operator /(const UBigInt &n) const
{
	int i;
	UBigInt result;
	if(*this<n)
	{
		result.lastdigit = 0;
		return result;
	}
	UBigInt remainder;
	UBigInt tmp;
	int low, high, mid;
	for(i=lastdigit; i>=0; i--)
	{
		if(remainder.lastdigit!=0 || remainder.digit[0]!=0)
			remainder.shift(1);
		remainder.digit[0] = digit[i];
		if(remainder<n)
			continue;
		// binary search for the digit of the quotient
		low = 1, high = MOD-1;
		while(low<=high)
		{
			mid = (low+high)>>1;
			tmp = n*mid;
			if(tmp>remainder)
				high = mid-1;
			else if(tmp<remainder)
				low = mid+1;
			else
				break;
		}

		if(result.lastdigit==-1)
			result.lastdigit = i;
		tmp = tmp-n;
		remainder = remainder-tmp;
		result.digit[i] = mid-1;
		if(remainder>=n)
		{
			remainder = remainder-n;
			result.digit[i]++;
		}
	}
	return result;
}

inline bool UBigInt::operator >=(const UBigInt &n) const
{
	if(lastdigit>n.lastdigit)
		return true;
	else if(lastdigit<n.lastdigit)
		return false;
	for(int i=lastdigit; i>=0; i--)
	{
		if(digit[i]>n.digit[i])
			return true;
		else if(digit[i]<n.digit[i])
			return false;
	}
	return true;
}

inline bool UBigInt::operator <=(const UBigInt &n) const
{
	if(lastdigit>n.lastdigit)
		return false;
	else if(lastdigit<n.lastdigit)
		return true;
	for(int i=lastdigit; i>=0; i--)
	{
		if(digit[i]>n.digit[i])
			return false;
		else if(digit[i]<n.digit[i])
			return true;
	}
	return true;
}

inline bool UBigInt::operator >(const UBigInt &n) const
{
	return !((*this)<=n);
}

inline bool UBigInt::operator <(const UBigInt &n) const
{
	return !((*this)>=n);
}

inline void UBigInt::print() const
{
	cout<<digit[lastdigit];
	cout.fill('0');
	for(int i=lastdigit-1; i>=0; i--)
	{
		cout.width(WIDTH);
		cout<<digit[i];
	}
}

#define MAXK 22
#define MAXD 22

UBigInt counting[MAXK][MAXD];
int node_num[MAXK][MAXD];

int main()
{
	unsigned int k, d;
	int i, j, l;
	for(i=1; i<MAXK; i++)
	{
		node_num[i][0] = 1;
		for(j=1; j<=(MAXD-1)/i; j++)
		{
			node_num[i][j] = node_num[i][j-1]*i+1;
		}
	}
	UBigInt tmp1, tmp2, fact;
	for(i=1; i<MAXK; i++)
	{
		counting[i][0] = 1;
		fact = 1;
		for(l=1; l<node_num[i][1]; l++)
			fact = fact*l;
		counting[i][1] = fact;
		tmp1 = 1;
		for(j=2; j<=(MAXD-1)/i; j++)
		{
			for(l=node_num[i][j-1]; l<node_num[i][j]; l++)
				fact = fact*l;
			tmp1 = tmp2 = tmp1*node_num[i][j-1];
			for(l=1; l<i; l++)
				tmp1 = tmp1*tmp2;
			counting[i][j] = fact/tmp1;
		}
	}
	while(cin>>k>>d)
	{
		counting[k][d].print();
		cout<<endl;
	}
	return 0;
}