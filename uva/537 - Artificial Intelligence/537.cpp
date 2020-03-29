#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int i, j, n;
	char line[1001];
	bool flag[3] = {false, false, false};
	double P, U, I, tmp;
	scanf("%d", &n);
	fgets(line, sizeof(line), stdin);
	for(i = 1; i <= n; i++)
	{
		fgets(line, sizeof(line), stdin);
		int len = strlen(line);
		line[--len] = 0;
		int begin, end;
		int k = 0;
		for(j = 0; j < len; j++)
		{
			if(line[j] == '=')
			{
				begin = j-1;
				j++;
				while(line[j] == '.' || line[j] >= '0' && line[j] <= '9')
					j++;
				if(line[j] == 'W' || line[j] == 'V' || line[j] == 'A')
					end = j;
				else
					end = ++j;

				tmp = atof(line+begin+2);
				switch(line[end-1])
				{
				case 'm':
					tmp /= 1000;
					break;
				case 'k':
					tmp *= 1000;
					break;
				case 'M':
					tmp *= 1000000;
				}
				switch(line[begin])
				{
				case 'P':
					P = tmp;
					flag[0] = true;
					break;
				case 'U':
					U = tmp;
					flag[1] = true;
					break;
				case 'I':
					I = tmp;
					flag[2] = true;
					break;
				}

				k++;
				if(k == 2)
				{
					if(!flag[0])
						printf("Problem #%d\nP=%.2lfW\n\n", i, U*I);
					else if(!flag[1])
						printf("Problem #%d\nU=%.2lfV\n\n", i, P/I);
					else
						printf("Problem #%d\nI=%.2lfA\n\n", i, P/U);
					flag[0] = flag[1] = flag[2] = false;
					break;
				}
			}
		}
	}
	return 0;
}
