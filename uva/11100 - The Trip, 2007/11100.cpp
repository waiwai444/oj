#include <stdio.h>
#include <algorithm>

int n;
int dim[10000];

void solve()
{
	std::sort(dim, dim+n);
	
	int i, j, piece_num = 0, count = 1;
	int cur_dim = dim[0];
	for(i = 1; i < n; i++)
	{
		if(dim[i] != cur_dim)
		{
			if(count > piece_num)
				piece_num = count;
			count = 1;
			cur_dim = dim[i];
		}
		else
			count++;
	}
	if(count > piece_num)
		piece_num = count;
	printf("%d\n", piece_num);
	
	for(i = 0; i < piece_num; i++)
	{
		printf("%d", dim[i]);
		for(j = i+piece_num; j < n; j += piece_num)
			printf(" %d", dim[j]);
		printf("\n");
	}
}

int main()
{
	int i;
	bool first = true;
	while(scanf("%d", &n), n)
	{
		if(!first)
			printf("\n");
		else
			first = false;
		for(i = 0; i < n; i++)
			scanf("%d", &dim[i]);
		solve();
	}
	return 0;
}
