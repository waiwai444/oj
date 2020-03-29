#include <stdio.h>
#include <string.h>

char str[101];

void solve()
{
	int i, j, k, len = (int)strlen(str), count[26];
	memset(count, 0, sizeof(count));
	
	for(i = 0; i < len; i++)
		++count[str[i]-'a'];
	
	int odd = 0;
	for(i = 0; i < 26; i++)
		if(count[i] & 1)
			++odd;
	if(odd > 1)
	{
		printf("Impossible\n");
		return;
	}
	
	int m = len/2;
	int result = 0;
	
	for(i = 0; i < m; i++)
	{
		if(str[i] == str[len-1-i])
			continue;
		j = len-1-i;
		while(str[j] != str[i])
			j--;
		k = i;
		while(str[k] != str[len-1-i])
			k++;
		if(len-1-j < k)
		{
			result += len-1-i-j;
			char tmp = str[j];
			while(++j < len-i)
				str[j-1] = str[j];
			str[j] = tmp;
		}
		else
		{
			result += k-i;
			char tmp = str[k];
			while(--k >= i)
				str[k+1] = str[k];
			str[i] = tmp;
		}
	}
	
	printf("%d\n", result);
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s", str);
		solve();
	}
	return 0;
}