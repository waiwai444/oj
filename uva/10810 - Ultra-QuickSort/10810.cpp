#include <stdio.h>

int num[500000];
int temp[500000];
long long inv;

void merge_sort(int i, int j)	// use merge sort to sort the numbers descending to count the inverse number
{
	if(i == j)
		return;
	int mid = (i+j)/2;
	merge_sort(i, mid);
	merge_sort(mid+1, j);
	int k = i, l = mid+1, p = i;
	while(k <= mid && l <= j)
	{
		if(num[k] > num[l])
		{
			temp[p++] = num[k++];
			inv += j-l+1;
		}
		else
		{
			temp[p++] = num[l++];
		}
	}
	while(k <= mid)
		temp[p++] = num[k++];
	while(l <= j)
		temp[p++] = num[l++];
	for(k = i; k <= j; k++)
		num[k] = temp[k];
}

int main()
{
	int i, n;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &num[i]);
		inv = 0;
		merge_sort(0, n-1);
		printf("%lld\n", inv);
	}
	return 0;
}
