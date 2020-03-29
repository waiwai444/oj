#include <stdio.h>
#include <string.h>

int n;
char ans[31];

long long factorial[16] = {
	1, 1, 2, 6, 24, 120, 720, 5040, 40320,
	362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000
};

void solve(char *str)
{
	static int cnt[26];
	int i, j, k, odd = 0, s;
	int len = strlen(str);
	long long t;
	char mid;
	memset(cnt, 0, sizeof(cnt));
	for(i = 0; i < len; i++)
	{
		++cnt[str[i]-'a'];
	}
	for(i = 0; i < 26; i++)
	{
		if(cnt[i]&1)
		{
			++odd;
			mid = i+'a';
		}
	}
	if((!(len&1) && odd > 0) || ((len&1) && odd > 1) || (len == 1 && n > 1))
	{
		strcpy(ans, "XXX");
		return;
	}
	ans[len] = '\0';
	if(len&1)
	{
		ans[len/2] = mid;
		--cnt[mid-'a'];
	}
	s = 0;
	for(i = 0; i < len/2; i++)
	{
		for(j = 0; j < 26; j++)
		{
			if(cnt[j] <= 0)
				continue;
			t = factorial[len/2-(i+1)];
			for(k = 0; k < 26; k++)
			{
				if(cnt[k] <= 0)
					continue;
				if(k == j)
					t /= factorial[cnt[k]/2-1];
				else
					t /= factorial[cnt[k]/2];
			}
			if(s+t >= n)
			{
				cnt[j] -= 2;
				ans[i] = ans[len-1-i] = j+'a';
				break;
			}
			s += t;
		}
		if(j == 26)
		{
			strcpy(ans, "XXX");
			return;
		}
	}
}

int main()
{
	int i, tc;
	char str[31];
	scanf("%d", &tc);
	for(i = 1; i <= tc; i++)
	{
		scanf("%s%d", str, &n);
		solve(str);
		printf("Case %d: %s\n", i, ans);
	}
	return 0;
}

