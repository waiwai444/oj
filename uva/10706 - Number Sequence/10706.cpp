#include <stdio.h>

#define MAX_K 100000
#define MAX_I 2147483647

int max_k;
int sk_len[MAX_K];
unsigned int sk_sum[MAX_K];

void generate_sk_len()
{
	int i, j, k, l;
	sk_len[0] = 0;
	for(i = 1, l = 1; i <= MAX_K/10; i *= 10, l++)
	{
		j = i*10;
		for(k = i; k < j; k++)
			sk_len[k] = sk_len[i-1]+(k-i+1)*l;
	}
	sk_sum[0] = sk_len[0];
	for(i = 1; i < MAX_K; i++)
	{
		sk_sum[i] = sk_sum[i-1]+sk_len[i];
		if(sk_sum[i] > MAX_I)
		{
			max_k = i;
			break;
		}
	}
}

int search_k(int pos)
{
	int i = 1, j = max_k, mid;
	while(i < j)
	{
		mid = (i+j)/2;
		if(pos <= sk_sum[mid] && pos > sk_sum[mid]-sk_len[mid])
			return mid;
		if(sk_sum[mid] < pos)
			i = mid+1;
		else
			j = mid-1;
	}
	return i;
}

int get_digit(int n, int pos)
{
	int i, len = 0, t = n;
	while(t)
	{
		len++;
		t /= 10;
	}
	t = 1;
	for(i = pos; i < len; i++)
		t *= 10;
	return n/t%10;
}

int solve(int pos)
{
	if(pos == 1)
		return 1;
	int i, j, k = search_k(pos), mid;
	pos -= sk_sum[k-1];
	i = 1;
	j = k;
	while(i <= j)
	{
		mid = (i+j)/2;
		if(sk_len[mid] < pos)
			i = mid+1;
		else if(sk_len[mid] > pos)
			j = mid-1;
		else
		{
			i = mid;
			break;
		}
	}
	pos -= sk_len[i-1];
	return get_digit(i, pos);
}

int main()
{
	int t, pos;
	generate_sk_len();
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &pos);
		printf("%d\n", solve(pos));
	}
	return 0;
}
