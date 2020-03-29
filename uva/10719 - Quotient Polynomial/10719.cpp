#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n, k, r;
int coef[10001];
int qcoef[10000];

char buf[125001];

int main()
{
	int i, j;
	char *ptr;
	while(scanf("%d", &k) != EOF)
	{
		fgets(buf, sizeof(buf), stdin);
		fgets(buf, sizeof(buf), stdin);
		coef[0] = atoi(strtok(buf, " "));
		n = 0;
		while(ptr = strtok(NULL, " "))
			coef[++n] = atoi(ptr);
		qcoef[0] = coef[0];
		for(i = 1; i < n; i++)
			qcoef[i] = coef[i]+k*qcoef[i-1];
		r = coef[n]+k*qcoef[n-1];
		ptr = buf;
		for(i = j = 0; i < n; i++)
			j = sprintf(ptr += j, " %d", qcoef[i]);
		printf("q(x):%s\nr = %d\n\n", buf, r);
	}
	return 0;
}
