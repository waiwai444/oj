#include <stdio.h>
#include <string.h>

char *left[2], *right;
size_t len_l[2], len_r;
int arabic_l[2];

char ch_to_digit[26];
char digit_to_ch[10];

int arabic_ans;

int roman_digit_to_arabic(char ch)
{
	switch(ch)
	{
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		case 'D':
			return 500;
		case 'M':
			return 1000;
	}
	return 0;
}

int parse_roman(char *roman)
{
	int result = 0, cur_num, next_num;
	while(*roman != '\0')
	{
		cur_num = roman_digit_to_arabic(*roman);
		if(*(roman+1) != '\0')
		{
			next_num = roman_digit_to_arabic(*(roman+1));
			if(cur_num < next_num)
				result -= cur_num;
			else
				result += cur_num;
		}
		else
			result += cur_num;
		roman++;
	}
	return result;
}

bool check_arabic_sum()
{
	int left_sum = arabic_l[0]+arabic_l[1];
	for(int i = (int)len_r-1; i >= 0; i--)
	{
		int digit = left_sum%10;
		int digit2 = ch_to_digit[right[i]-'A'];
		if(i == 0 && digit == 0)
			return false;
		if(digit2 != -1 && digit != digit2)
			return false;
		left_sum /= 10;
	}
	if(left_sum > 0)
		return false;
	arabic_ans++;
	return arabic_ans > 1;
}

bool backtrack(int num_idx, int cur)
{
	char ch;
	if(cur < len_l[num_idx])
	{
		ch = left[num_idx][cur]-'A';
		if(ch_to_digit[ch] != -1)
		{
			arabic_l[num_idx] = arabic_l[num_idx]*10+ch_to_digit[ch];
			if(backtrack(num_idx, cur+1))
				return true;
			arabic_l[num_idx] /= 10;
		}
		else
		{
			int first_digit = 0;
			int last_digit = 9;
			if(cur == 0)	// pruning
			{
				first_digit = 1;
				if(len_r > len_l[0] && len_r > len_l[1])
				{
					if(len_l[num_idx] > len_l[1-num_idx])
						first_digit = 9;
					else if(len_l[0] == len_l[1] && left[0][0] == left[1][0])
						first_digit = 5;
				}
				else if(len_l[0] == len_l[1])
				{
					if(left[0][0] == left[1][0])
						last_digit = 4;
					else
						last_digit = 8;
				}
			}
			
			// backtrack
			for(int i = first_digit; i <= last_digit; i++)
			{
				if(digit_to_ch[i] == -1)
				{
					digit_to_ch[i] = ch;
					ch_to_digit[ch] = i;
					
					arabic_l[num_idx] = arabic_l[num_idx]*10+i;
					if(backtrack(num_idx, cur+1))
						return true;
					arabic_l[num_idx] /= 10;
					
					digit_to_ch[i] = ch_to_digit[ch] = -1;
				}
			}
		}
	}
	else
	{
		if(num_idx == 0)
		{
			if(backtrack(1, 0))
				return true;
		}
		else
		{
			return check_arabic_sum();
		}
	}
	return false;
}

int main()
{
	int n1, n2, nr;
	char input[30];
	while(scanf("%s", input), input[0] != '#')
	{
		left[0] = strtok(input, "+");
		left[1] = strtok(NULL, "=");
		right = strtok(NULL, "\n");
		
		n1 = parse_roman(left[0]);
		n2 = parse_roman(left[1]);
		nr = parse_roman(right);
		len_l[0] = strlen(left[0]);
		len_l[1] = strlen(left[1]);
		len_r = strlen(right);
		
		n1+n2 == nr ? printf("Correct ") : printf("Incorrect ");
		
		if((len_r > len_l[0]+1 && len_r > len_l[1]+1) || len_r < len_l[0] || len_r < len_l[1]
		   || (len_l[0] == len_l[1] && len_l[0] == len_r && (left[0][0] == right[0] || left[1][0] == right[0])))
			printf("impossible\n");
		else
		{
			memset(ch_to_digit, -1, sizeof(ch_to_digit));
			memset(digit_to_ch, -1, sizeof(digit_to_ch));
			arabic_l[0] = arabic_l[1] = 0;
			arabic_ans = 0;
			
			backtrack(0, 0);
			
			if(arabic_ans == 0)
				printf("impossible\n");
			else if(arabic_ans == 1)
				printf("valid\n");
			else
				printf("ambiguous\n");
		}
	}
	return 0;
}