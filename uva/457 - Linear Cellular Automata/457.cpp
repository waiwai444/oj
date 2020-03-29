#include <stdio.h>

int main()
{
	int i, j, f, tc;
	int dna[10];
	int dish[2][40];
	char output[41];
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d%d%d%d%d%d%d%d%d", &dna[0], &dna[1], &dna[2], &dna[3], &dna[4], &dna[5], &dna[6], &dna[7], &dna[8], &dna[9]);
		for(i = 0; i < 40; i++)
			dish[0][i] = 0;
		dish[0][19] = 1;
		f = 0;
		for(i = 0; i < 50; i++)
		{
			for(j = 0; j < 40; j++)
			{
				switch(dish[f][j])
				{
				case 0:
					output[j] = ' ';
					break;
				case 1:
					output[j] = '.';
					break;
				case 2:
					output[j] = 'x';
					break;
				case 3:
					output[j] = 'W';
					break;
				}
			}
			output[40] = '\0';
			printf("%s\n", output);

			dish[1-f][0] = dna[dish[f][0]+dish[f][1]];
			for(j = 1; j < 39; j++)
				dish[1-f][j] = dna[dish[f][j-1]+dish[f][j]+dish[f][j+1]];
			dish[1-f][39] = dna[dish[f][38]+dish[f][39]];
			f = 1-f;
		}
		if(tc)
			printf("\n");
	}
	return 0;
}
