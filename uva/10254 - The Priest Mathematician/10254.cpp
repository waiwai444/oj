#include <cstdio>

class UBigInt {
	const static int MAXDIGIT = 10;
	const static int MOD = 1000000000;
	const static int WIDTH = 9;
	long long digit[MAXDIGIT];
	int lastdigit;

	void clear();
public:
	UBigInt();
	UBigInt(unsigned long long n);
	UBigInt operator =(unsigned long long n);
	UBigInt operator +(const UBigInt &n) const;
	void print() const;
};

inline void UBigInt::clear()
{
	for(int i=0; i<MAXDIGIT; i++)
		digit[i] = 0;
	lastdigit = -1;
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

inline UBigInt UBigInt::operator +(const UBigInt &n) const
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

inline void UBigInt::print() const
{
	printf("%d", digit[lastdigit]);
	for(int i=lastdigit-1; i>=0; i--)
		printf("%0*d", WIDTH, digit[i]);
}

UBigInt steps[10001];

int main()
{
	int i, j, l;
	int n;
	UBigInt d(1);
	steps[0] = 0;
	i = l = 1;
	while(i<=10000)
	{
		for(j=0; j<l && i+j<=10000; j++)
			steps[i+j] = steps[i+j-1]+d;
		i += l;
		l++;
		d = d+d;
	}
	while(scanf("%d", &n)!=EOF)
	{
		steps[n].print();
		printf("\n");
	}
	return 0;
}