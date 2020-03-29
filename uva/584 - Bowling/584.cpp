#include <stdio.h>
#include <string.h>

int score[11][2];

void parse(char *line)
{
	int i;
	char *ch;
	memset(score, 0, sizeof(score));
	ch = strtok(line, " ");
	if(*ch == 'X')
		score[0][0] = 10;
	else
	{
		score[0][0] = *ch-'0';
		ch = strtok(NULL, " ");
		score[0][1] = *ch == '/' ? 10-score[0][0] : *ch-'0';
	}
	i = 1;
	while(ch = strtok(NULL, " "))
	{
		if(*ch == 'X')
		{
			score[i][0] = 10;
			if(i == 10)
			{
				ch = strtok(NULL, " ");
				if(!ch)
					break;
				score[i][1] = *ch == 'X' ? 10 : *ch-'0';
			}
		}
		else
		{
			score[i][0] = *ch-'0';
			ch = strtok(NULL, " ");
			if(!ch)
				break;
			score[i][1] = *ch == '/' ? 10-score[i][0] : *ch-'0';
		}
		++i;
	}
}

int solve()
{
	int i, total = 0;
	for(i = 0; i < 10; i++)
	{
		total += score[i][0];
		if(score[i][0] == 10)
		{
			total += score[i+1][0];
			if(i < 9 && score[i+1][0] == 10)
				total += score[i+2][0];
			else
				total += score[i+1][1];
			continue;
		}
		total += score[i][1];
		if(score[i][0]+score[i][1] == 10)
		{
			total += score[i+1][0];
		}
	}
	return total;
}

int main()
{
	char line[50];
	while(fgets(line, 50, stdin))
	{
		if(strncmp(line, "Game Over", 9) == 0)
			break;
		parse(line);
		printf("%d\n", solve());
	}
	return 0;
}
