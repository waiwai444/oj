#include <stdio.h>
#include <string.h>

class BigUInt
{
    char digit[500];
    int ndigits;
public:
    BigUInt() : ndigits(0) {}

    void get_from_str(char *str)
    {
        int i = 0, len = strlen(str);
        while(i < len && str[i] == '0')
            i++;
        ndigits = len-i;
        while(i < len)
        {
            digit[len-i-1] = str[i]-'0';
            i++;
        }
    }
    void reset() { ndigits = 0; }

    BigUInt operator *(const BigUInt& num)
    {
        int i, j, carry(0), pos;
        BigUInt result;
        for(i = 0; i < num.ndigits; i++)
        {
            for(j = 0; j < ndigits; j++)
            {
                pos = i+j;
                if(pos == result.ndigits)
                    result.digit[result.ndigits++] = 0;
                result.digit[pos] += num.digit[i]*digit[j]+carry;
                if(result.digit[pos] >= 10)
                {
                    carry = result.digit[pos]/10;
                    result.digit[pos] = result.digit[pos]%10;
                }
                else
                    carry = 0;
            }
            if(carry > 0)
            {
                result.digit[result.ndigits++] = carry;
                carry = 0;
            }
         }
         return result;
    }

    friend void println_biguint(const BigUInt& num);
};

void println_biguint(const BigUInt& num)
{
    int i;
    if(num.ndigits == 0)
    {
        printf("0\n");
        return;
    }
    char output[501];
    for(i = num.ndigits-1; i >= 0; i--)
        output[num.ndigits-1-i] = num.digit[i]+'0';
    output[num.ndigits] = '\0';
    printf("%s\n", output);
}

BigUInt x, y, r;

int main()
{
    int i, len;
    char line[300];
    while(scanf("%s", line) != EOF)
    {
        x.get_from_str(line);
        scanf("%s", line);
        y.get_from_str(line);

        r = x*y;
        println_biguint(r);
        x.reset();
        y.reset();
    }
    return 0;
}
