#include <stdio.h>
#include <string.h>

#define USE_LEFT -1
#define USE_RIGHT -2
#define MATCHED -3

char input[101];
int input_len;

struct dp_state_t
{
	int min_len;
	int next;
} dp[100][100];

char result[201];

void solve()
{
	int i, j, k, d, min, tmp, p;
	char *ptr;
	for(i = 0; i < input_len; i++)
	{
		dp[i][i].min_len = 2;
		if(input[i] == '(' || input[i] == '[')
			dp[i][i].next = USE_LEFT;
		else
			dp[i][i].next = USE_RIGHT;
	}
	for(d = 1; d < input_len; d++)
	{
		for(i = 0; i+d < input_len; i++)
		{
			j = i+d;
			min = 999;
			// concatenation
			for(k = i+1; k <= j; k++)
			{
				if((tmp = dp[i][k-1].min_len+dp[k][j].min_len) < min)
				{
					min = tmp;
					p = k;
				}
			}
			// nested
			if(input[i] == '(' && input[j] == ')' || input[i] == '[' && input[j] == ']')
			{
				if((tmp = dp[i+1][j-1].min_len+2) < min) // including d == 1
				{
					min = tmp;
					p = MATCHED;
				}
			}
			if((input[i] == '(' || input[i] == '[') && (tmp = dp[i+1][j].min_len+2) < min)
			{
				min = tmp;
				p = USE_LEFT;
			}
			if((input[j] == ')' || input[j] == ']') && (tmp = dp[i][j-1].min_len+2) < min)
			{
				min = tmp;
				p = USE_RIGHT;
			}
			//
			dp[i][j].min_len = min;
			dp[i][j].next = p;
		}
	}
}

void get_result_recur(int l, int r, int res_l, int res_r)
{
	if(l > r)
		return;
	if(dp[l][r].next == MATCHED)
	{
		result[res_l] = input[l];
		result[res_r] = input[r];
		get_result_recur(l+1, r-1, res_l+1, res_r-1);
	}
	else if(dp[l][r].next == USE_LEFT)
	{
		result[res_l] = input[l];
		result[res_r] = input[l] == '(' ? ')' : ']';
		get_result_recur(l+1, r, res_l+1, res_r-1);
	}
	else if(dp[l][r].next == USE_RIGHT)
	{
		result[res_l] = input[r] == ')' ? '(' : '[';
		result[res_r] = input[r];
		get_result_recur(l, r-1, res_l+1, res_r-1);
	}
	else
	{
		int m = dp[l][r].next;
		get_result_recur(l, m-1, res_l, res_l+dp[l][m-1].min_len-1);
		get_result_recur(m, r, res_l+dp[l][m-1].min_len, res_r);
	}
}

void get_result(int l, int r, int res_l, int res_r)
{
	get_result_recur(l, r, res_l, res_r);
	result[res_r+1] = '\0';
}

int main()
{
	int tc;
	char line[150];
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%d", &tc);
	while(tc--)
	{
		fgets(line, sizeof(line), stdin);
		fgets(line, sizeof(line), stdin);
		input[0] = '\0';
		sscanf(line, "%s", input);
		input_len = strlen(input);

		solve();

		if(input_len > 0)
		{
			get_result(0, input_len-1, 0, dp[0][input_len-1].min_len-1);
			printf("%s\n", result);
		}
		else
			printf("\n");
		if(tc)
			printf("\n");
	}
	return 0;
}
