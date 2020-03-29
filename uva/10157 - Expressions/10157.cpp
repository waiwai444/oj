#include <cstdio>

using namespace std;

class UBigInt {
	const static int MAXDIGIT = 50;
	const static int MOD = 10000;
	const static int WIDTH = 4;
	long digit[MAXDIGIT];
	int lastdigit;

	void clear();
public:
	UBigInt();
	UBigInt(unsigned int x);
	void print() const;
	UBigInt operator =(unsigned int x);
	UBigInt operator +(const UBigInt &x) const;
	UBigInt operator -(const UBigInt &x) const;
	UBigInt operator *(const UBigInt &x) const;
};

inline void UBigInt::clear()
{
	for(int i=0; i<MAXDIGIT; i++)
		digit[i] = 0;
	lastdigit = -1;
}

inline void UBigInt::print() const
{
	printf("%ld", digit[lastdigit]);
	for(int i=lastdigit-1; i>=0; i--)
		printf("%0*d", WIDTH, digit[i]);
}

UBigInt::UBigInt()
{
	clear();
}

UBigInt::UBigInt(unsigned int x)
{
	clear();
	if(x<MOD)
	{
		digit[0] = x;
		lastdigit = 0;
		return;
	}
	while(x>0)
	{
		digit[++lastdigit] = x%MOD;
		x /= MOD;
	}
}

inline UBigInt UBigInt::operator =(unsigned int x)
{
	*this = UBigInt(x);
	return x;
}

UBigInt UBigInt::operator +(const UBigInt &x) const
{
	int i;
	int l = lastdigit>=x.lastdigit?lastdigit:x.lastdigit;
	long carry = 0;
	UBigInt result;
	for(i=0; i<=l ;i++)
	{
		result.digit[i] = digit[i]+x.digit[i]+carry;
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
		result.digit[i] = 1;
		result.lastdigit = i;
	}
	else
		result.lastdigit = i-1;
	return result;
}

UBigInt UBigInt::operator -(const UBigInt &x) const
{
	int i;
	long borrow = 0;
	UBigInt result;
	result.lastdigit = 0;
	for(i=0; i<=lastdigit; i++)
	{
		result.digit[i] = digit[i]-x.digit[i]-borrow;
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

UBigInt UBigInt::operator *(const UBigInt &x) const
{
	int i, j;
	long carry = 0;
	UBigInt result;
	for(i=0; i<=x.lastdigit; i++)
	{
		for(j=0; j<=lastdigit; j++)
		{
			result.digit[i+j] += x.digit[i]*digit[j]+carry;
			if(result.digit[i+j]>=MOD)
			{
				carry = result.digit[i+j]/MOD;
				result.digit[i+j] = result.digit[i+j]%MOD;
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

#define MAXN 150
#define MAXD 150

UBigInt counting[MAXN+1][MAXD+1];

int main()
{
	int m, n, d;
	int i, j, k;
	counting[0][0] = counting[1][1] = 1;
	for(i=2; i<=MAXN; i++)
	{
		counting[i][1] = 1;
		for(j=2; j<i; j++)
		{
			counting[i][j] = 0;
			for(k=0; k<i; k++)
				counting[i][j] = counting[i][j]+counting[k][j-1>k?k:j-1]*counting[i-k-1][j>i-k-1?i-k-1:j];
		}
		counting[i][i] = counting[i][i-1]+1;
	}
	while(scanf("%d %d", &n, &d)!=EOF)
	{
		if((n&1)!=0 || (m=n>>1)<d)
		{
			printf("0\n");
			continue;
		}
		if(d==1 || d==m)
		{
			printf("1\n");
			continue;
		}
		(counting[m][d]-counting[m][d-1]).print();
		printf("\n");
	}
	return 0;
}