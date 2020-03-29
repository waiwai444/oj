
#include <stdio.h>
#include <algorithm>

struct Elephant
{
	int id;
	int weight;
	int iq;
};

Elephant eleph[1000];
int nelephs;

bool cmp(const Elephant& e1, const Elephant& e2)
{
	return e1.weight < e2.weight;
}

int dptable[1000];
int dpparent[1000];

void output(int pos, int step)
{
	if(dpparent[pos] == -1)
		printf("%d\n", step);
	else
		output(dpparent[pos], step + 1);
	printf("%d\n", eleph[pos].id);
}

int main()
{
	int i, j;
	while(scanf("%d%d", &eleph[nelephs].weight, &eleph[nelephs].iq) != EOF)
	{
		eleph[nelephs].id = nelephs + 1;
		++nelephs;
	}
	std::sort(eleph, eleph + nelephs, cmp);
	dptable[0] = 1;
	dpparent[0] = -1;
	for(i = 1; i < nelephs; i++)
	{
		dptable[i] = 1;
		dpparent[i] = -1;
		for(j = 0; j < i; j++)
		{
			if(eleph[j].weight < eleph[i].weight && eleph[j].iq > eleph[i].iq && dptable[j] >= dptable[i])
			{
				dptable[i] = dptable[j] + 1;
				dpparent[i] = j;
			}
		}
	}
	for(i = j = 0; i < nelephs; i++)
		if(dptable[i] > dptable[j])
			j = i;
	output(j, 1);
	return 0;
}
