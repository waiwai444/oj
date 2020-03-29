#include <stdio.h>
#include <string.h>
#include <limits.h>

int nbox, dim;
int box[30][10];
bool adj_mat[30][30];
int longest[30];
int lnext[30];

bool flag[30];
bool smaller(int b1, int b2)
{
	int i, j, d = -1, v;
	memset(flag, false, sizeof(flag));
	for(i = 0; i < dim; i++)
	{
		v = INT_MAX;
		for(j = 0; j < dim; j++)
		{
			if(!flag[j] && box[b1][i] < box[b2][j] && box[b2][j] < v)
			{
				v = box[b2][j];
				d = j;
			}
		}
		if(v == INT_MAX)
			return false;
		flag[d] = true;
	}
	return true;
}

void construct_graph()
{
	memset(adj_mat, false, sizeof(adj_mat));
	for(int i = 0; i < nbox; i++)
		for(int j = 0; j < nbox; j++)
			if(i != j && smaller(i, j))
				adj_mat[i][j] = true;
}

void dfs(int bi)
{
	int i;
	longest[bi] = 1;
	for(i = 0; i < nbox; i++)
	{
		if(adj_mat[bi][i])
		{
			if(longest[i] == 0)
				dfs(i);
			if(longest[bi] < longest[i]+1)
			{
				longest[bi] = longest[i]+1;
				lnext[bi] = i;
			}
		}
	}
}

void find_longest()
{
	int i;
	memset(longest, 0, sizeof(longest));
	memset(lnext, -1, sizeof(lnext));
	for(i = 0; i < nbox; i++)
	{
		if(longest[i] == 0)
		{
			dfs(i);
		}
	}
}

void output()
{
	int i, li = -1, ll = 0;
	for(i = 0; i < nbox; i++)
		if(longest[i] > ll)
		{
			ll = longest[i];
			li = i;
		}
	printf("%d\n%d", ll, li+1);
	for(i = lnext[li]; i != -1; i = lnext[i])
		printf(" %d", i+1);
	printf("\n");
}

int main()
{
	int i, j;
	while(scanf("%d%d", &nbox, &dim) != EOF)
	{
		for(i = 0; i < nbox; i++)
			for(j = 0; j < dim; j++)
				scanf("%d", &box[i][j]);
		construct_graph();
		find_longest();
		output();
	}
	return 0;
}
