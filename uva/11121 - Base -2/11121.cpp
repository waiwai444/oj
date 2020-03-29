#include <stdio.h>

int n, pos;
char res[100];

void recur(int n)
{
	if(n == 0)
		return;
	if(n > 0 || n%2 == 0)
		recur(n/(-2));
	else
		recur(n/(-2)+1);
	res[pos++] = n%2 ? '1' : '0';
}

void solve()
{
	pos = 0;
	recur(n);
	if(pos == 0)
		res[pos++] = '0';
	res[pos] = '\0';
}

int main()
{
	int tc, c;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%d", &n);
		printf("Case #%d: ", c);
		solve();
		printf("%s\n", res);
	}
	return 0;
}
