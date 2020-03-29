#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int teamRank[100];
int acNum[100];	// the number of AC problems for each team
bool acProblem[100][9];	// record if some problem is AC for some team
int penaltyTime[100];

void bubblesort()
{
	int i, j, t;
	int temp;
	bool stop;
	for(i=1; i<100; i++)
	{
		stop = true;
		for(j=0; j<100-i; j++)
		{
			if(acNum[teamRank[j]]<acNum[teamRank[j+1]] || acNum[teamRank[j]]==acNum[teamRank[j+1]] && penaltyTime[teamRank[j]]>penaltyTime[teamRank[j+1]])
			{
				t = teamRank[j], teamRank[j] = teamRank[j+1], teamRank[j+1] = t;
				stop = false;
			}
		}
		if(stop)
			break;
	}
}

int main()
{
	int i, d;
	int dataNum;
	int incorrect[100][9];	// record the number of incorrect submission of each problem for each team
	int teamId, problemId, submitTime;
	char status;
	char line[64];
	cin>>dataNum;
	cin.getline(line, 64);
	cin.getline(line, 64);
	for(d=0; d<dataNum; d++)
	{
		memset(acNum, -1, sizeof(acNum));
		memset(acProblem, false, sizeof(acProblem));
		memset(penaltyTime, 0, sizeof(penaltyTime));
		memset(incorrect, 0, sizeof(incorrect));
		while(cin.getline(line, 64))
		{
			if(line[0]==0)
				break;
			teamId = atoi(strtok(line, " "))-1;
			problemId = atoi(strtok(NULL, " "))-1;
			submitTime = atoi(strtok(NULL, " "));
			status = *strtok(NULL, " ");
			if(acNum[teamId]==-1)
				acNum[teamId] = 0;	// imply that this team has submmited at least once
			if(status=='C')
			{
				if(acProblem[teamId][problemId]==false)
				{
					acProblem[teamId][problemId] = true;
					acNum[teamId]++;
					penaltyTime[teamId] += submitTime;
					penaltyTime[teamId] += incorrect[teamId][problemId]*20;
				}
			}
			else if(status=='I')
			{
				incorrect[teamId][problemId]++;
			}
		}
		for(i=0; i<100; i++)
		{
			teamRank[i] = i;
		}
		bubblesort();
		for(i=0; i<100 && acNum[teamRank[i]]>=0; i++)
		{
			cout<<teamRank[i]+1<<' '<<acNum[teamRank[i]]<<' '<<penaltyTime[teamRank[i]]<<endl;
		}
		if(d<dataNum-1)
			cout<<endl;
	}
	return 0;
}