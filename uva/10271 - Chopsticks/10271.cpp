#include <stdio.h>

#define MAX_EATERS 1008
#define MAX_STICKS 5000
#define INF 0x3f3f3f3f

int neaters, nsticks;
int stick[MAX_STICKS];
int dptable[2][MAX_EATERS];	// record the total "badness"

int main()
{
	int i, j, test_case, badness, temp;
	scanf("%d", &test_case);
	while(test_case-- > 0)
	{
		scanf("%d%d", &neaters, &nsticks);
		neaters += 8;
		for(i = 0; i < nsticks; i++)
			scanf("%d", &stick[i]);
		for(j = 0; j < neaters; j++)
			dptable[0][j] = dptable[1][j] = INF;
		for(i = nsticks - 3; i >= 0; i--)
		{
			badness = (stick[i + 1] - stick[i]) * (stick[i + 1] - stick[i]);
			temp = dptable[1][0];
			dptable[1][0] = dptable[0][0];
			if(badness < dptable[0][0])
				dptable[0][0] = badness;
			for(j = 1; j < neaters; j++)
			{
				if(i + (j + 1) * 3 > nsticks)
					break;
				badness = (stick[i + 1] - stick[i]) * (stick[i + 1] - stick[i]) + temp;
				temp = dptable[1][j];
				dptable[1][j] = dptable[0][j];
				if(badness < dptable[0][j])
					dptable[0][j] = badness;
			}
		}
		printf("%d\n", dptable[0][neaters - 1]);
	}
	return 0;
}
