#include <stdio.h>
#include <string.h>

int main()
{
	int i, j, round, alpha_count[26], turn_over, word_len, nwrong;
	char word[30], guess[30];
	bool wrong_guess[26];
	while(scanf("%d", &round), round != -1)
	{
		scanf("%s%s", word, guess);
		memset(alpha_count, 0, sizeof(alpha_count));
		memset(wrong_guess, false, sizeof(wrong_guess));
		word_len = 0;
		while(word[word_len] != '\0')
		{
			alpha_count[word[word_len]-'a']++;
			word_len++;
		}
		i = turn_over = nwrong = 0;
		while(guess[i] != '\0')
		{
			j = guess[i]-'a';
			if(alpha_count[j] > 0)
			{
				turn_over += alpha_count[j];
				alpha_count[j] = 0;
				if(turn_over == word_len)
					goto win;
			}
			else if(!wrong_guess[j])
			{
				wrong_guess[j] = true;
				nwrong++;
				if(nwrong == 7)
					goto lose;
			}
			i++;
		}
		printf("Round %d\nYou chickened out.\n", round);
		continue;
win:
		printf("Round %d\nYou win.\n", round);
		continue;
lose:
		printf("Round %d\nYou lose.\n", round);
	}
	return 0;
}
