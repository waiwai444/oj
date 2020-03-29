#include <stdio.h>
#include <vector>

int n;
std::vector<int> result;

void output()
{
	printf("%d", result[0]);
	for(int i = 1; i < result.size(); i++)
		printf(" %d", result[i]);
	printf("\n");
}

int least_depth()
{
	int least = 1, tmp = n-1;
	while(tmp > 0)
	{
		tmp /= 2;
		least++;
	}
	return least;
}

bool reachable(int cur_depth, int max_depth, int sum)
{
	int t = max_depth-cur_depth, r = sum;
	for(int i = 0; i < t; i++)
		if((r *= 2) >= n)
			return true;
	return false;
}

bool iddfs(int max_depth)	// n > 2
{
	size_t i, j;
	int cur_depth = result.size()+1;
	int cur_max = result.back(), sum, old_sum = 0;
	i = j = result.size()-1;
	sum = result[i]+result[j];
	while(sum > cur_max)
	{
		if(cur_depth == max_depth)
		{
			if(sum == n)
			{
				result.push_back(n);
				return true;
			}
			else if(sum < n)
				return false;
		}
		else
		{
			if(sum < n && sum != old_sum)
			{
				if(!reachable(cur_depth, max_depth, sum))
					return false;
				else
				{
					result.push_back(sum);
					//output();
					if(iddfs(max_depth))
						return true;
					result.pop_back();
				}
			}
		}
		
		if(i == 0 && j == 0)
			break;
		else if(i == 0)
			j--;
		else if(j == 0)
			i--;
		else
		{
			if(result[i-1]+result[j] >= result[i]+result[j-1])
				i--;
			else
				j--;
		}
		old_sum = sum;
		sum = result[i]+result[j];
	}
	return false;
}

int main()
{
	int i;
	result.reserve(100);
	while(scanf("%d", &n), n)
	{
		if(n == 1)
			printf("1\n");
		else if(n == 2)
			printf("1 2\n");
		else
		{
			result.clear();
			result.push_back(1);
			result.push_back(2);
			i = least_depth();
			while(true)
				if(iddfs(i++))
					break;
			output();
		}
	}
	return 0;
}
