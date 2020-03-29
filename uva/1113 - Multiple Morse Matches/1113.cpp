#include <stdio.h>
#include <string.h>

#define MAX_MORSE_STR_LEN 1000
#define MAX_WORD_NUM 10000
#define MAX_WORD_LEN 100
#define MAX_WORD_CODE_LEN 400 

const int code_len[26] = {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 3, 4, 3, 4, 4, 4};
const char code[26][5] = {
	".-", "-...", "-.-.", "-..",
	".", "..-.", "--.", "....",
	"..", ".---", "-.-", ".-..",
	"--", "-.", "---", ".--.",
	"--.-", ".-.", "...", "-",
	"..-", "...-", ".--", "-..-",
	"-.--", "--.."
};

char morse_str[MAX_MORSE_STR_LEN+1];
int morse_len;
int word_num;
struct word_info_t
{
	char code[MAX_WORD_CODE_LEN+1];
	int code_len;
} word_info[MAX_WORD_NUM];

int dp[MAX_MORSE_STR_LEN+1];

void transcoding(int i, const char word[])
{
	int idx;
	char *ptr = word_info[i].code;
	while(*word)
	{
		idx = *word-'A';
		strcpy(ptr, code[idx]);
		ptr += code_len[idx];
		++word;
	}
	*ptr = '\0';
	word_info[i].code_len = ptr-word_info[i].code;
}

void init()
{
	memset(dp, 0, sizeof(dp));
}

void solve()
{
	int i, j, k;
	morse_len = strlen(morse_str);
	for(i = 0; i < morse_len; i++)
	{
		if(i == 0 || dp[i-1])
		{
			for(j = 0; j < word_num; j++)
			{
				if(i+word_info[j].code_len > morse_len)
					continue;
				for(k = 0; k < word_info[j].code_len; k++)
					if(word_info[j].code[k] != morse_str[i+k])
						break;
				if(k == word_info[j].code_len)
					dp[i+k-1] += (i==0?1:dp[i-1]);
			}
		}
	}
}

int main()
{
	int i, tc;
	char word[MAX_WORD_LEN+1];
	scanf("%d", &tc);
	while(tc--)
	{
		init();
		scanf("%s%d", morse_str, &word_num);
		for(i = 0; i < word_num; i++)
		{
			scanf("%s", word);
			transcoding(i, word);
		}
		solve();
		printf("%d\n", dp[morse_len-1]);
		if(tc)
			printf("\n");
	}
	return 0;
}
