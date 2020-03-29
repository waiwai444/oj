#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

int n;
int weights[100];
bool ssmap[51][22501];	// ssmap[i][j]==true indicates that there are i persons that are summed up to j before the current one. Only half of n is needed.
int subset_sum[51][15000];	// subset_sum[i] records different weight sums of i persons before the current one. subset_sum[i][0] is the number of different sums.

int main()
{
	int d, i, j, k;
	int max_sum;
	scanf("%d", &d);
	while(d--)
	{
		scanf("%d", &n);
		max_sum = 0;
		for(i=0; i<n; i++)
		{
			scanf("%d", &weights[i]);
			max_sum += weights[i];
		}

		// DP
		memset(ssmap, false, sizeof(ssmap));
		subset_sum[0][1] = 0;
		subset_sum[0][0] = 1;
		subset_sum[1][1] = weights[0];
		subset_sum[1][2] = weights[1];
		subset_sum[1][0] = 2;
		subset_sum[2][1] = weights[0]+weights[1];
		subset_sum[2][0] = 1;
		ssmap[0][0] = ssmap[1][weights[0]] = ssmap[1][weights[1]] = ssmap[2][weights[0]+weights[1]] = true;
		for(i=2; i<n; i++)
		{
			if(i<n/2)
				subset_sum[i+1][0] = 0;
			for(j=(i<n/2?i:n/2-1); j>=0; j--)
			{
				for(k=1; k<=subset_sum[j][0]; k++)
				{
					if(!ssmap[j+1][subset_sum[j][k]+weights[i]])
					{
						ssmap[j+1][subset_sum[j][k]+weights[i]] = true;
						subset_sum[j+1][++subset_sum[j+1][0]] = subset_sum[j][k]+weights[i];
					}
				}
			}
		}

		// Find out the result
		j = 1;
		int min_diff = abs(max_sum/2-subset_sum[n/2][j]);
		int diff;
		for(i=2; i<=subset_sum[n/2][0]; i++)
		{
			diff = abs(max_sum/2-subset_sum[n/2][i]);
			if(diff<min_diff)
			{
				min_diff = diff;
				j = i;
			}
		}
		if(max_sum-subset_sum[n/2][j]>=subset_sum[n/2][j])
			printf("%d %d\n", subset_sum[n/2][j], max_sum-subset_sum[n/2][j]);
		else
			printf("%d %d\n", max_sum-subset_sum[n/2][j], subset_sum[n/2][j]);

		if(d)
			printf("\n");
	}
	return 0;
}