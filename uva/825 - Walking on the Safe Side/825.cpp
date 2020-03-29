#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int w, n;
bool unsafe[100][100];
int count[100][100];

int main()
{
	int i, j, tc;
	char input[500], *chptr;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &w, &n);
		fgets(input, 500, stdin);
		memset(unsafe, false, sizeof(unsafe));
		for(i = 0; i < w; i++)
		{
			fgets(input, 500, stdin);
			strtok(input, " ");
			while((chptr = strtok(NULL, " ")))
				unsafe[i][atoi(chptr)-1] = true;
		}
		count[0][0] = unsafe[0][0] ? 0 : 1;
		for(i = 1; i < w; i++)
			count[i][0] = unsafe[i][0] ? 0 : count[i-1][0];
		for(j = 1; j < n; j++)
			count[0][j] = unsafe[0][j] ? 0 : count[0][j-1];
		for(i = 1; i < w; i++)
			for(j = 1; j < n; j++)
			{
				count[i][j] = 0;
				if(!unsafe[i][j])
				{
					count[i][j] += count[i-1][j]+count[i][j-1];
				}
			}
		printf("%d\n", count[w-1][n-1]);
		if(tc)
			printf("\n");
	}
	return 0;
}