#include <stdio.h>
#include <string.h>

int count[26];

char vowel_v[] = { 'A', 'U', 'E', 'O', 'I' };
char consonant_v[] = { 'J', 'S', 'B', 'K', 'T', 'C', 'L', 'D', 'M', 'V', 'N', 'W', 'F', 'X', 'G', 'P', 'Y', 'H', 'Q', 'Z', 'R' };
char vowel_a[] = { 'A', 'E' ,'I', 'O', 'U' };
char consonant_a[] = { 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };

int main()
{
	int i, j, tc, n;
	char name[212];
	scanf("%d", &tc);
	for(i = 1; i <= tc; i++)
	{
		scanf("%d", &n);

		int vn, cn;
		if((n&1) == 1)
		{
			cn = n/2;
			vn = cn+1;
		}
		else
			cn = vn = n/2;
		for(j = 0; j < 5; j++)
		{
			if(vn >= 21)
			{
				count[vowel_v[j]-'A'] = 21;
				vn -= 21;
			}
			else
			{
				count[vowel_v[j]-'A'] = vn;
				vn = 0;
			}
		}
		for(j = 0; j < 21; j++)
		{
			if(cn >= 5)
			{
				count[consonant_v[j]-'A'] = 5;
				cn -= 5;
			}
			else
			{
				count[consonant_v[j]-'A'] = cn;
				cn = 0;
			}
		}

		int ci = 0, vi = 0;
		for(j = 1; j <= n; j++)
		{
			if((j&1) == 1)
			{
				while(count[vowel_a[vi]-'A'] == 0)
					vi++;
				name[j-1] = vowel_a[vi];
				count[vowel_a[vi]-'A']--;
			}
			else
			{
				while(count[consonant_a[ci]-'A'] == 0)
					ci++;
				name[j-1] = consonant_a[ci];
				count[consonant_a[ci]-'A']--;
			}
		}
		name[n] = '\0';
		printf("Case %d: %s\n", i, name);
	}
	return 0;
}