#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

char candidates[20][81];
int cnum;
int poll[20];
bool out[20];
int ballot[1000][20];
int bnum;

int main()
{
	int i, j, t;
	int s;
	int max;
	int maxArr[20];	// temporarily store candidate indices whose polls are the largest
	int maxArrSize;
	int min;
	int minArr[20];
	int minArrSize;
	char line[81];
	cin>>s;
	cin.getline(line, 81);
	cin.getline(line, 81);
	for(t=0; t<s; t++)
	{
		cin>>cnum;
		cin.getline(line, 81);
		for(i=0; i<cnum; i++)
		{
			cin.getline(line, 81);
			strcpy(candidates[i], line);
		}
		memset(out, 0, sizeof(out));

		bnum = 0;
		while(cin.getline(line, 81))
		{
			if(line[0]==0)
				break;
			ballot[bnum][0] = atoi(strtok(line, " "));
			for(i=1; i<cnum; i++)
			{
				ballot[bnum][i] = atoi(strtok(NULL, " "));
			}
			bnum++;
		}

		while(true)
		{
			memset(poll, 0, sizeof(poll));
			// count the polls
			for(i=0; i<bnum; i++)
			{
				for(j=0; j<cnum; j++)
				{
					if(!out[ballot[i][j]-1])
					{
						poll[ballot[i][j]-1]++;
						break;
					}
				}
			}
			// find out the max and the min
			max = -1;
			min = -1;
			maxArrSize = 0;
			minArrSize = 0;
			for(i=0; i<cnum; i++)
			{
				if(!out[i])
				{
					if(min==-1 || min>poll[i])
					{
						min = poll[i];
						minArrSize = 1;
						minArr[minArrSize-1] = i;
					}
					else if(min==poll[i])
					{
						minArr[minArrSize++] = i;
					}
					if(max<poll[i])
					{
						max = poll[i];
						maxArrSize = 1;
						maxArr[maxArrSize-1] = i;
					}
					else if(max==poll[i])
					{
						maxArr[maxArrSize++] = i;
					}
				}
			}
			// see if someone is elected
			if((double)max/bnum>0.5)
			{
				cout<<candidates[maxArr[0]]<<endl;
				break;
			}
			else if(max==min)
			{
				for(i=0; i<cnum; i++)
				{
					if(!out[i])
						cout<<candidates[i]<<endl;
				}
				break;
			}
			else
			{
				for(i=0; i<minArrSize; i++)
				{
					out[minArr[i]] = true;
				}
			}
		}
		if(t!=s-1)
			cout<<endl;
	}
	return 0;
}