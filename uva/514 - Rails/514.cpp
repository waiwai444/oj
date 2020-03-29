#include <stdio.h>
#include <vector>

int main()
{
	int i, c, n;
	int target[1000];
	std::vector<int> station;
	while(scanf("%d", &n), n)
	{
		while(scanf("%d", &target[0]), target[0])
		{
			for(i = 1; i < n; i++)
				scanf("%d", &target[i]);
			station.clear();
			c = 1;
			for(i = 0; i < n; i++)
			{
				if(!station.empty() && station.back() == target[i])
					station.pop_back();
				else
				{
					while(c <= n && c < target[i])
						station.push_back(c++);
					if(c <= n)
						c++;
					else
						break;
				}
			}
			if(i == n)
				printf("Yes\n");
			else
				printf("No\n");
		}
		printf("\n");
	}
	return 0;
}