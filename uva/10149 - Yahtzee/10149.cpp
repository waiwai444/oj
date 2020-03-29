#include <iostream>
#include <cstdlib>
#include <memory.h>

using namespace std;


void bubblesort(int arr[])
{
	int i, j, t;
	bool stop;
	for(i=1; i<5; i++)
	{
		stop = true;
		for(j=0; j<5-i; j++)
		{
			if(arr[j]>arr[j+1])
			{
				t = arr[j], arr[j] = arr[j+1], arr[j+1] = t;
				stop = false;
			}
		}
	}
}

void getScore(int dice[], int score[])
{
	int i;
	bubblesort(dice);
	for(i=0; i<5; i++)
	{
		score[6] += dice[i];	// chance
		switch(dice[i])
		{
		case 1:
			score[0]++;	//ones
			break;
		case 2:
			score[1] += 2;	// twos
			break;
		case 3:
			score[2] += 3;	// threes
			break;
		case 4:
			score[3] += 4;	// fours
			break;
		case 5:
			score[4] += 5;	//fives
			break;
		case 6:
			score[5] += 6;	//sixes
			break;
		}
	}
	if(dice[0]==dice[2] || dice[1]==dice[3] || dice[2]==dice[4])
	{
		score[7] = score[6];	// three of a kind
		if(dice[0]==dice[3] || dice[1]==dice[4])
		{
			score[8] = score[6];	// four of a kind
			if(dice[0]==dice[4])
				score[9] = 50;	// five of a kind
		}
		if(dice[0]==dice[2] && dice[3]==dice[4] || dice[2]==dice[4] && dice[0]==dice[1])
			score[12] = 40;	// full house
	}
	else if(dice[1]==dice[2]-1 && dice[2]==dice[3]-1 && (dice[0]==dice[1]-1 || dice[3]==dice[4]-1))
	{
		score[10] = 25;	// short straight
		if(dice[4]-dice[0]==4)
			score[11] = 35;	//long straight
	}
}

#define STATENUM (1<<13)
#define MAXFIRSTSIX 116

struct State {
	int max[MAXFIRSTSIX];
	int lastCategory[MAXFIRSTSIX];
};

State state[STATENUM];

int main()
{
	int i, j, k;
	int score[13][13];
	int dice[5];
	int ones;	// the number of bits that are 1s
	int loc[13];	// record which bit is 1
	int temp;
	State subState;
	while(cin>>dice[0]>>dice[1]>>dice[2]>>dice[3]>>dice[4])
	{
		memset(score, 0, sizeof(score));
		getScore(dice, score[0]);
		for(i=1; i<13; i++)
		{
			cin>>dice[0]>>dice[1]>>dice[2]>>dice[3]>>dice[4];
			getScore(dice, score[i]);
		}

		memset(state, -1, sizeof(state));
		for(i=1; i<STATENUM; i++)
		{
			ones = 0;
			for(j=0; j<13; j++)
			{
				if((i&(1<<j))>0)
				{
					loc[ones++] = j;
				}
			}
			if(ones==1)
			{
				temp = score[0][loc[0]];
				if(loc[0]<6)
				{
					state[i].max[temp] = temp;
					state[i].lastCategory[temp] = loc[0];
				}
				else
				{
					state[i].max[0] = temp;
					state[i].lastCategory[0] = loc[0];
				}
			}
			else
			{
				for(j=0; j<ones; j++)
				{
					subState = state[i-(1<<loc[j])];
					temp = score[ones-1][loc[j]];
					for(k=0; k<MAXFIRSTSIX; k++)
					{
						if(subState.max[k]==-1)
							continue;
						if(loc[j]<6)
						{
							if(state[i].max[k+temp]<subState.max[k]+temp)
							{
								state[i].max[k+temp] = subState.max[k]+temp;
								state[i].lastCategory[k+temp] = loc[j];
							}
						}
						else
						{
							if(state[i].max[k]<subState.max[k]+temp)
							{
								state[i].max[k] = subState.max[k]+temp;
								state[i].lastCategory[k] = loc[j];
							}
						}
					}
				}
			}
		}
		for(i=63; i<MAXFIRSTSIX; i++)
		{
			if(state[STATENUM-1].max[i]!=-1)
				state[STATENUM-1].max[i] += 35;
		}
		int max = -1;
		int finalFirstSix = -1;
		for(i=0; i<MAXFIRSTSIX; i++)
		{
			if(max<state[STATENUM-1].max[i])
			{
				max = state[STATENUM-1].max[i];
				finalFirstSix = i;
			}
		}
		int category[13];
		j = STATENUM-1;
		k = finalFirstSix;
		for(i=12; i>=0; i--)
		{
			category[i] = state[j].lastCategory[k];
			if(category[i]<6)
				k -= score[i][category[i]];
			j -= (1<<category[i]);
		}
		for(i=0; i<13; i++)
		{
			for(j=0; j<13; j++)
			{
				if(category[j]==i)
				{
					cout<<score[j][i]<<' ';
					break;
				}
			}
		}
		if(finalFirstSix>=63)
			cout<<35<<' ';
		else
			cout<<0<<' ';
		cout<<state[STATENUM-1].max[finalFirstSix]<<endl;
	}
	return 0;
}