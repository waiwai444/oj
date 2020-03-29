#include <stdio.h>

#define MAX_STATION 100
#define TANK_CAPACITY 200
#define INIT_TANK 100

int distance;

struct GasStation
{
	int dist;
	int price;
} station[MAX_STATION];
int nstations;

int dptable[TANK_CAPACITY + 1];

int main()
{
	int test_case, i, j, temp;
	char buf[32];
	scanf("%d", &test_case);
	while(test_case-- > 0)
	{
		bool too_far = false;
		scanf("%d", &distance);
		getchar();
		nstations = 0;
		while(fgets(buf, sizeof(buf), stdin) != NULL && buf[0] != '\n')
		{
			sscanf(buf, "%d%d", &station[nstations].dist, &station[nstations].price);
			if(too_far)
				continue;
			if(nstations == 0)
				nstations++;
			else if(station[nstations].dist > station[nstations - 1].dist)
			{
				if(station[nstations].dist - station[nstations - 1].dist > TANK_CAPACITY)
				{
					too_far = true;
					continue;
				}
				nstations++;
			}
			else if(station[nstations].price < station[nstations - 1].price)
				station[nstations - 1].price = station[nstations].price;
		}
		if(distance == 0)
			printf("0\n");
		else if(nstations == 0 || station[0].dist > INIT_TANK || distance - station[nstations - 1].dist > (TANK_CAPACITY - INIT_TANK) || too_far)
			printf("Impossible\n");
		else
		{
			temp = INIT_TANK - station[0].dist;
			for(j = 0; j <= temp; j++)
				dptable[j] = 0;
			for(j = temp + 1; j <= TANK_CAPACITY; j++)
				dptable[j] = dptable[j - 1] + station[0].price;
			for(i = 1; i < nstations; i++)
			{
				dptable[0] = dptable[station[i].dist - station[i - 1].dist];
				for(j = 1; j <= TANK_CAPACITY; j++)
				{
					dptable[j] = dptable[j - 1] + station[i].price;
					if(j + station[i].dist - station[i - 1].dist <= TANK_CAPACITY && dptable[j] > (temp = dptable[j + station[i].dist - station[i - 1].dist]))
						dptable[j] = temp;
				}
			}
			printf("%d\n", dptable[INIT_TANK + distance - station[nstations - 1].dist]);
		}
		if(test_case > 0)
			printf("\n");
	}
	return 0;
}
