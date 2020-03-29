#include <stdio.h>
#include <string.h>

int main()
{
	int i, j, k, l, n, m, x[7], order[7], tc = 0;
	const int step[] = { 1, 2, 4, 8, 16, 32, 64 };
	char line[31], leaf[130];
	char result[129];
	while(scanf("%d", &n), n)
	{
		fgets(line, sizeof(line), stdin);
		fgets(line, sizeof(line), stdin);
		line[strlen(line)-1] = 0;
		for(j = 0, i = 1; line[i] != '\0'; i++)
			if(line[i] >= '1' && line[i] <= '7')
				order[j++] = line[i]-'0'-1;
		fgets(leaf, sizeof(leaf), stdin);
		leaf[strlen(leaf)-1] = 0;
		scanf("%d", &m);
		fgets(line, sizeof(line), stdin);
		for(l = 0; l < m; l++)
		{
			fgets(line, sizeof(line), stdin);
			line[strlen(line)-1] = 0;
			for(i = 0; line[i] != '\0'; i++)
				x[i] = line[i]-'0';
			for(i = j = 0, k = n-1; i < n; i++, k--)
			{
				if(x[order[i]] == 1)
					j += step[k];
			}
			result[l] = leaf[j];
		}
		result[l] = '\0';
		printf("S-Tree #%d:\n%s\n\n", ++tc, result);
	}
	return 0;
}
