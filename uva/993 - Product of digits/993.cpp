#include <stdio.h>
#include <algorithm>

int n;

void solve()
{
	if(n <= 1)
	{
		printf("%d\n", n);
		return;
	}

	int i, nd = 0;
	char digit[30];
	
	for(i = 9; i > 1; i--)
	{
		while(n%i == 0)
		{
			digit[nd++] = i+'0';
			n /= i;
		}
	}
	
	if(n == 1)
	{
		std::reverse(digit, digit+nd);
		digit[nd] = '\0';
		printf("%s\n", digit);
	}
	else
		printf("-1\n");
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		solve();
	}
	return 0;
}
