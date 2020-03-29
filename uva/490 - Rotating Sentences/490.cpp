#include <stdio.h>
#include <string.h>

int n;
char sentence[101][105];
char output[11000];

int main()
{
	int i, j, k;
	bool flag;
	while(fgets(sentence[n], sizeof(sentence[n]), stdin))
	{
		sentence[n][strlen(sentence[n])-1] = 0;
		n++;
	}
	if(n > 0)
	{
		k = 0;
		for(i = 0; i < 101; i++)
		{
			flag = false;
			for(j = n-1; j >= 0; j--)
			{
				if(sentence[j][i] == 0)
					output[k++] = ' ';
				else
					output[k++] = sentence[j][i];
				if(sentence[j][i] != 0)
					flag = true;
			}
			output[k++] = '\n';
			if(!flag)
				break;
		}
		output[k-n-1] = '\0';
		printf("%s", output);
	}
	return 0;
}
