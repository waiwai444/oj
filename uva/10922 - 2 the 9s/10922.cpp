#include <cstdio>
#include <cstring>

char num[1001];

int recur(int n)
{
	int s = 0;
	if(n == 9)
		return 1;
	while(n)
	{
		s += n%10;
		n /= 10;
	}
	return recur(s)+1;
}

void solve()
{
	int i, s = 0;
	int len = strlen(num);
	for(i = 0; i < len; i++)
		s += num[i]-'0';
	if(s%9)
	{
		printf("%s is not a multiple of 9.\n", num);
		return;
	}
	int d = recur(s);
	printf("%s is a multiple of 9 and has 9-degree %d.\n", num, d);
}

int main()
{
	while(scanf("%s", num), num[0] != '0')
		solve();
	return 0;
}

