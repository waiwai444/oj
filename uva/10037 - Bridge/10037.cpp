#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	int i;
	int d;
	int n;
	vector<int> cost;
	vector<int> order;
	int total_cost;
	int remaining;
	cost.reserve(1000);
	order.reserve(3000);
	scanf("%d\n", &d);
	while(d-->0)
	{
		scanf("%d", &n);
		cost.resize(n);
		for(i=0; i<n; i++)
			scanf("%d", &cost[i]);
		if(n==1)
			printf("%d\n%d\n", cost[0], cost[0]);
		else
			sort(cost.begin(), cost.end());
		if(n>1)
		{
			total_cost = 0;
			remaining = n;
			while(true)
			{
				if(remaining==2)
				{
					order.push_back(cost[0]);
					order.push_back(cost[1]);
					total_cost += cost[1];
					break;
				}
				else if(remaining==3)
				{
					order.push_back(cost[0]);
					order.push_back(cost[2]);
					order.push_back(cost[0]);
					order.push_back(cost[0]);
					order.push_back(cost[1]);
					total_cost += cost[2]+cost[0]+cost[1];
					break;
				}
				if(2*cost[1]<=cost[0]+cost[remaining-2])
				{
					order.push_back(cost[0]);
					order.push_back(cost[1]);
					order.push_back(cost[0]);
					order.push_back(cost[remaining-2]);
					order.push_back(cost[remaining-1]);
					order.push_back(cost[1]);
					total_cost += 2*cost[1]+cost[0]+cost[remaining-1];
				}
				else
				{
					order.push_back(cost[0]);
					order.push_back(cost[remaining-1]);
					order.push_back(cost[0]);
					order.push_back(cost[0]);
					order.push_back(cost[remaining-2]);
					order.push_back(cost[0]);
					total_cost += 2*cost[0]+cost[remaining-1]+cost[remaining-2];
				}
				remaining -= 2;
			}
			
			printf("%d\n", total_cost);
			for(i=0; i<order.size(); i+=3)
			{
				printf("%d %d\n", order[i], order[i+1]);
				if(i+2<order.size())
					printf("%d\n", order[i+2]);
			}
		}
		if(d>0)
		{
			order.clear();
			printf("\n");
		}
	}
	return 0;
}