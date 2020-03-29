
#include <stdio.h>
#include <algorithm>

struct Turtle
{
	int weight;
	int strength;
};

bool cmp(const Turtle& t1, const Turtle& t2)
{
	return t1.strength < t2.strength; // t1.strength - t1.weight - t2.weight < t2.strength - t2.weight - t1.weight;
}

int num;
Turtle turtles[5607];

//int min_weight[5607][5608];
int min_weight[5608];

int main()
{
	int i, j, tmp, weight, strength, max_height = 0;
	while(scanf("%d%d", &weight, &strength) != EOF)
	{
		if(strength >= weight)
		{
			turtles[num].weight = weight;
			turtles[num++].strength = strength;
		}
	}
	if(num > 0)
	{
		std::sort(turtles, turtles + num, cmp);
		min_weight[1] = turtles[0].weight;
		max_height = 1;
	}
	for(i = 1; i < num; i++)
	{
		for(j = max_height; j >= 1; j--)
		{
			tmp = min_weight[j] + turtles[i].weight;
			if(tmp <= turtles[i].strength && (j == max_height || tmp < min_weight[j + 1]))
			{
				min_weight[j + 1] = tmp;
				if(j == max_height)
					max_height++;
			}
		}
		if(turtles[i].weight < min_weight[1])
			min_weight[1] = turtles[i].weight;
	}
	printf("%d\n", max_height);
	return 0;
}
