#include <stdio.h>
#include <string.h>

#define MAXN 1000

int main()
{
	int i, n, tc = 0, strong, all;
	int code[MAXN];
	int guess[MAXN];
	int code_count[10];
	int guess_count[10];
	while(scanf("%d", &n), n)
	{
		memset(code_count, 0, sizeof(code_count));
		for(i = 0; i < n; i++)
		{
			scanf("%d", &code[i]);
			code_count[code[i]]++;
		}
		printf("Game %d:\n", ++tc);
		while(1)
		{
			memset(guess_count, 0, sizeof(guess_count));
			for(i = 0; i < n; i++)
			{
				scanf("%d", &guess[i]);
				guess_count[guess[i]]++;
			}
			if(guess[0] == 0)
				break;
			strong = all = 0;
			for(i = 0; i < n; i++)
				if(code[i] == guess[i])
					strong++;
			for(i = 1; i <= 9; i++)
				all += (code_count[i] <= guess_count[i] ? code_count[i] : guess_count[i]);
			printf("    (%d,%d)\n", strong, all-strong);
		}
	}
	return 0;
}