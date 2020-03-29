#include <stdio.h>
#include <string.h>

int main()
{
	int n;
	char skewb[35];
	while(fgets(skewb, sizeof(skewb), stdin))
	{
		int len = strlen(skewb);
		skewb[--len] = 0;
		if(len == 1 && skewb[0] == '0')
			break;
		n = 0;
		int p = 2;
		for(int i = len-1; i >= 0; i--)
		{
			n += (skewb[i]-'0')*(p-1);
			p *= 2;
		}
		printf("%d\n", n);
	}
	return 0;
}
