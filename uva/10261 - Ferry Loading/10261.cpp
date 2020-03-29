#include <stdio.h>

#define MAX_CAR 210
#define MAX_LEN 10000

#define INVALID -2
#define NO_CAR -1

int car[MAX_CAR];
int dptable[MAX_CAR][MAX_LEN + 1];

void print_result(int cur_car, int port_len)
{
	if(cur_car == 0)
	{
		if(port_len > 0)
			printf("port\n");
		else
			printf("starboard\n");
	}
	else
	{
		if(dptable[cur_car][port_len] == cur_car)
		{
			print_result(cur_car - 1, port_len - car[cur_car]);
			printf("port\n");
		}
		else
		{
			print_result(cur_car - 1, port_len);
			printf("starboard\n");
		}
	}
}

int main()
{
	int i, j, test_case, ferry_len, ncars, total_sum, car_on_board;
	scanf("%d", &test_case);
	while(test_case-- > 0)
	{
		scanf("%d", &ferry_len);
		ferry_len *= 100;
		ncars = 0;
		while(scanf("%d", &car[ncars]))
		{
			if(car[ncars] == 0)
				break;
			ncars++;
		}
		car_on_board = -1;
		
		if(ncars > 0 && car[0] <= ferry_len)
		{
			for(j = 0; j <= ferry_len; j++)
				dptable[0][j] = INVALID;
			dptable[0][0] = NO_CAR;
			dptable[0][car[0]] = 0;
			car_on_board = 0;
			total_sum = car[0];
			for(i = 1; i < ncars; i++)
			{
				for(j = 0; j <= ferry_len; j++)
				{
					if(j >= car[i] && dptable[i - 1][j - car[i]] > INVALID)	// on port
					{
						dptable[i][j] = i;
						car_on_board = i;
					}
					else if(dptable[i - 1][j] > INVALID && total_sum - j + car[i] <= ferry_len)	// on starboard
					{
						dptable[i][j] = dptable[i - 1][j];
						car_on_board = i;
					}
					else
						dptable[i][j] = INVALID;
				}
				if(car_on_board != i)
					break;
				total_sum += car[i];
			}
		}
		printf("%d\n", car_on_board + 1);
		if(car_on_board >= 0)
		{
			for(j = ferry_len; j >= 0; j--)
				if(dptable[car_on_board][j] > INVALID)
					break;
			print_result(car_on_board, j);
		}
		if(test_case > 0)
			printf("\n");
	}
	return 0;
}
