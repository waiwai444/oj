#include <stdio.h>
#include <string.h>

int prime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

int fac_num[101];
int factors[101][10];

int result[101][101];
int res_len[101];

int main()
{
	int i, j, n, t;
	memset(fac_num, 0, sizeof(fac_num));
	for(i = 2; i <= 100; i++)
	{
		for(j = 0; j < 25; j++)
		{
			if(prime[j] > i)
				break;
			if(i%prime[j] == 0)
			{
				t = i;
				do
				{
					factors[i][fac_num[i]++] = prime[j];
					t /= prime[j];
				} while(t%prime[j] == 0);
			}
		}
	}
	memset(result, 0, sizeof(result));
	memset(res_len, 0, sizeof(res_len));
	for(i = 2; i <= 100; i++)
	{
		memcpy(result[i], result[i-1], sizeof(result[i-1]));
		for(j = 0; j < fac_num[i]; j++)
			result[i][factors[i][j]]++;
		for(j = 24; j >= 0; j--)
			if(result[i][prime[j]] != 0)
			{
				res_len[i] = j+1;
				break;
			}
	}
	while(scanf("%d", &n), n)
	{
		printf("%3d! =", n);
		for(i = 0; i < res_len[n]; i++)
		{
			printf("%3d", result[n][prime[i]]);
			if(i < res_len[n]-1 && i == 14)
				printf("\n      ");
		}
		printf("\n");
	}
	return 0;
}