
#include <stdio.h>
#include <string.h>

#define MAXSEQ 10000
#define MAXSUB 100

class UBigInt	// unsigned big int
{
	static const int MAXLEN = 101;
	char digit[MAXLEN];	// 101 digits
	int len;
public:
	UBigInt()
	{
		digit[0] = 0;
		len = 1;
	}
	
	UBigInt(int num)
	{
		int i = 0;
		if(num == 0)
		{
			digit[0] = 0;
			len = 1;
			return;
		}
		while(num != 0)
		{
			digit[i++] = num % 10;
			num /= 10;
		}
		len = i;
	}
	
	UBigInt& operator=(const UBigInt& num)
	{
		len = num.len;
		for(int i = 0; i < len; i++)
			digit[i] = num.digit[i];
		return *this;
	}
	
	UBigInt operator+(const UBigInt& num)
	{
		int i;
		UBigInt new_num;
		char carry = 0;
		for(i = 0; i < len || i < num.len || carry; i++)
		{
			new_num.digit[i] = 0;
			if(i < len)
				new_num.digit[i] += digit[i];
			if(i < num.len)
				new_num.digit[i] += num.digit[i];
			new_num.digit[i] += carry;
			if(new_num.digit[i] >= 10)
			{
				new_num.digit[i] -= 10;
				carry = 1;
			}
			else
				carry = 0;
		}
		new_num.len = i;
		return new_num;
	}
	
	UBigInt& operator+=(const UBigInt& num)
	{
		return *this = *this + num;
	}
	
	void println()
	{
		int i;
		char buf[MAXLEN];
		for(i = 0; i < len; i++)
			buf[len - i - 1] = digit[i] + '0';
		buf[len] = '\0';
		printf("%s\n", buf);
	}
};

char seq[MAXSEQ + 1];
char subseq[MAXSUB + 1];
int seq_len;
int sub_len;

UBigInt dptable[MAXSUB][MAXSEQ];

int main()
{
	int i, j;
	int test_case;
	scanf("%d", &test_case);
	while(test_case-- > 0)
	{
		scanf("%s%s", seq, subseq);
		seq_len = strlen(seq);
		sub_len = strlen(subseq);
		if(seq_len < sub_len)
		{
			printf("0\n");
			continue;
		}
		if(seq[0] == subseq[0])
			dptable[0][0] = 1;
		else
			dptable[0][0] = 0;
		for(i = 1; i < seq_len; i++)
		{
			dptable[0][i] = dptable[0][i - 1];
			if(seq[i] == subseq[0])
				dptable[0][i] += 1;
		}
		for(i = 1; i < sub_len; i++)
			dptable[i][0] = 0;
		for(i = 1; i < sub_len; i++)
		{
			for(j = 1; j < seq_len; j++)
			{
				dptable[i][j] = dptable[i][j - 1];
				if(seq[j] == subseq[i])
					dptable[i][j] += dptable[i - 1][j - 1];
			}
		}
		dptable[sub_len - 1][seq_len - 1].println();
	}
	return 0;
}
