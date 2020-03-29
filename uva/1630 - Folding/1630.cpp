#include <stdio.h>
#include <string.h>

char seq[101];
int len;

int dp[100][100];
bool rep[100][100][100];
struct partition_t
{
	int pos;
	bool rep;
} part[100][100];

char result[101];

int num_len(int num)
{
	int len = 0;
	while(num)
	{
		++len;
		num /= 10;
	}
	return len;
}

void init_rep()
{
	int i, j, k, l;
	memset(rep, false, sizeof(rep));
	for(i = 0; i < len; i++)
	{
		for(j = 1; j <= (len-i)/2; j++)
		{
			//rep[i][i+j-1][j] = true;
			for(k = i+j; k < len; k += j)
			{
				for(l = k; l < k+j; l++)
				{
					if(seq[l] != seq[l-j])
						break;
				}
				if(l == k+j)
					rep[i][l-1][j] = true;
				else
					break;
			}
		}
		//rep[i][len-1][len-i] = true;
	}
}

void solve()
{
	int i, j, k, d, tmp;
	init_rep();
	for(i = 0; i < len; i++)
		dp[i][i] = 1;
	for(d = 1; d < len; d++)
	{
		for(i = 0; i+d < len; i++)
		{
			j = i+d;
			dp[i][j] = d+1;
			part[i][j].rep = false;
			part[i][j].pos = i+1;
			// concatenation
			for(k = i+1; k <= j; k++)
			{
				tmp = dp[i][k-1]+dp[k][j];
				if(tmp < dp[i][j])
				{
					dp[i][j] = tmp;
					part[i][j].pos = k;
				}
			}
			// repeat
			for(k = 1; k <= (d+1)/2; k++)
			{
				if(rep[i][j][k])
				{
					tmp = num_len((d+1)/k)+2+dp[i][i+k-1];
					if(tmp < dp[i][j])
					{
						dp[i][j] = tmp;
						part[i][j].rep = true;
						part[i][j].pos = k;
					}
				}
			}
		}
	}
}

int get_result(int i, int j, int r)
{
	if(i == j)
	{
		result[r++] = seq[i];
	}
	else if(part[i][j].rep)
	{
		int times = (j-i+1)/part[i][j].pos;
		r += sprintf(&result[r], "%d", times);
		result[r] = '(';
		r = get_result(i, i+part[i][j].pos-1, r+1);
		result[r++] = ')';
	}
	else
	{
		r = get_result(i, part[i][j].pos-1, r);
		r = get_result(part[i][j].pos, j, r);
	}
	return r;
}

void print_result()
{
	get_result(0, len-1, 0);
	result[dp[0][len-1]] = '\0';
	printf("%s\n", result);
}

int main()
{
	while(scanf("%s", seq) != EOF)
	{
		len = strlen(seq);
		solve();
		print_result();
	}
	return 0;
}
