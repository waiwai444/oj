#include <stdio.h>
#include <string.h>

int main()
{
	const int base = 100000;
	const int base_digit = 5;
	int i, j, r, n, fpos, ndigits;
	int result[25];
	char line[11];
	char output[128];
	while(fgets(line, sizeof(line), stdin))
	{
		line[strlen(line)-1] = 0;
		r = 0;
		fpos = 0;
		for(i = 0; i < 6; i++)
			if(line[i] == '.')
				fpos = 5-i;
			else
				r = r*10+line[i]-'0';
		n = line[8]-'0';
		if(line[7] != ' ')
			n += (line[7]-'0')*10;
		fpos *= n;
		
		// multiplication of big integers with specified base
		result[0] = r;
		ndigits = 1;
		for(i = 1; i < n; i++)
		{
			int carry = 0;
			for(j = 0; j < ndigits; j++)
			{
				long long temp = (long long)result[j]*r+carry;
				result[j] = (int)(temp%base);
				carry = (int)(temp/base);
			}
			if(carry > 0)
			{
				result[j] = carry;
				ndigits++;
			}
		}
		
		// get the position of the fraction point
		int fpos_base = fpos/base_digit;
		fpos = fpos%base_digit;
		if(fpos > 0)
			fpos_base++;
		else
			fpos = base_digit;
		if(fpos_base > ndigits)
			memset(result+ndigits, 0, (fpos_base-ndigits)*sizeof(int));
		
		// make output
		int k = 0;
		char temp_str[base_digit];
		bool fp_printed = false;
		for(i = (fpos_base > ndigits ? fpos_base : ndigits)-1; i >= 0; i--)
		{
			for(j = base_digit-1; j >= 0; j--)
			{
				temp_str[j] = result[i]%10+'0';
				result[i] /= 10;
			}
			for(j = 0; j < base_digit; j++)
			{
				if(!fp_printed && i == fpos_base-1 && j+fpos == base_digit)
				{
					output[k++] = '.';
					fp_printed = true;
				}
				output[k++] = temp_str[j];
			}
		}
		output[k] = '\0';
		if(fp_printed)
			while(--k >= 0)
			{
				if(output[k] == '.')
				{
					output[k--] = '\0';
					break;
				}
				else if(output[k] != '0')
				{
					output[k+1] = '\0';
					break;
				}
			}		
		for(i = 0; i <= k; i++)
		{
			if(output[i] != '0')
				break;
		}
		printf("%s\n", output+i);		
	}
	return 0;
}
