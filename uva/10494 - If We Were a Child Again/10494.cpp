#include <stdio.h>
#include <string.h>

#define SIZE 5000

struct BigUInt
{
	char digit[SIZE];
	int ndigits;

	BigUInt() : ndigits(0) {}
};

void get_big_uint(char *in, BigUInt* out)
{
	int ndigits = strlen(in);
	int i = 0, j;
	while(i < ndigits && in[i] == '0')
		i++;
	for(j = i; j < ndigits; j++)
		out->digit[j-i] = in[ndigits-1-(j-i)]-'0';
	out->ndigits = ndigits-i;
}

int main()
{
	BigUInt x, quot;
	int i, y, rem;
	long long partial_dividend;
	char op, op_tmp[2], str_x[SIZE], result[SIZE];

	while(scanf("%s%s%d", str_x, op_tmp, &y) != EOF)
	{
		op = op_tmp[0];
		get_big_uint(str_x, &x);
		if(x.ndigits == 0)
		{
			printf("0\n");
			continue;
		}

		partial_dividend = 0;
		quot.ndigits = x.ndigits;
		for(i = x.ndigits-1; i >= 0; i--)
		{
			partial_dividend = partial_dividend*10+x.digit[i];
			quot.digit[i] = partial_dividend/y;
			partial_dividend %= y;
		}
		rem = partial_dividend;
		if(op == '/')
		{
			for(i = quot.ndigits-1; i >= 0; i--)
			{
				if(quot.digit[i] != 0)
					break;
				else
					quot.ndigits--;
			}
			if(quot.ndigits == 0)
				printf("0\n");
			else
			{
				for(i = quot.ndigits-1; i >= 0; i--)
					result[quot.ndigits-1-i] = quot.digit[i]+'0';
				result[quot.ndigits] = '\0';
				printf("%s\n", result);
			}
		}
		else if(op == '%')
		{
			printf("%d\n", rem);
		}
	}

	return 0;
}