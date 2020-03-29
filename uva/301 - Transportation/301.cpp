#include <stdio.h>
#include <string.h>
#include <algorithm>

int capacity, station_num, order_num;

struct Order
{
	int passenger_num;
	int start, dest;
	int earnings;
} orders[22];

int remaining_earnings[22];
int passenger_num[8];
int max_earnings;

bool cmp(const Order& o1, const Order& o2)
{
	return o1.start < o2.start;
}

bool available(const Order& order)
{
	for(int i = order.start; i < order.dest; i++)
		if(passenger_num[i]+order.passenger_num > capacity)
			return false;
	return true;
}

void try_take_orders(int order_idx, int cur_earnings)
{
	int i, j;
	
	if(cur_earnings > max_earnings)
		max_earnings = cur_earnings;

	for(i = order_idx; i < order_num; i++)
	{
		if(available(orders[i]) && remaining_earnings[i]+cur_earnings > max_earnings)
		{
			for(j = orders[i].start; j < orders[i].dest; j++)
				passenger_num[j] += orders[i].passenger_num;
			
			try_take_orders(i+1, cur_earnings+orders[i].earnings);
			
			for(j = orders[i].start; j < orders[i].dest; j++)
				passenger_num[j] -= orders[i].passenger_num;
		}
	}
}

int main()
{
	int i;
	while(scanf("%d%d%d", &capacity, &station_num, &order_num), capacity || station_num || order_num)
	{
		for(i = 0; i < order_num; i++)
		{
			scanf("%d%d%d", &orders[i].start, &orders[i].dest, &orders[i].passenger_num);
			orders[i].earnings = orders[i].passenger_num*(orders[i].dest-orders[i].start);
		}
		std::sort(orders, orders+order_num, cmp);
		memset(passenger_num, 0, sizeof(passenger_num));
		memset(remaining_earnings, 0, sizeof(remaining_earnings));
		remaining_earnings[order_num-1] = orders[order_num-1].earnings;
		for(i = order_num-2; i >= 0; i--)
			remaining_earnings[i] = remaining_earnings[i+1]+orders[i].earnings;
		
		max_earnings = 0;
		try_take_orders(0, 0);
		printf("%d\n", max_earnings);
	}
	return 0;
}