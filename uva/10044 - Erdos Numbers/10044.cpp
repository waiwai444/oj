// Some constants about the size or the length of the input can be seen in algorithmist.com for uva10044
#include <stdio.h>
#include <map>
#include <string>
#include <string.h>
#include <vector>

#define AUTHORNUM 5000
#define NAMESIZE 130
#define LINELENGTH 10005

using namespace std;

struct CooperationInfo {
	int erdosNum;
	vector<int> coauthor;
};

CooperationInfo cooperation[AUTHORNUM];
map<string, int> nameSet;	// author names and the indices of the corresponding cooperation info.

// bfs to calcalute erdos numbers from Erdos, P.
void calcErdosNum()
{
	int i, s;
	CooperationInfo *ci, *ci2;
	int authorIdx[AUTHORNUM];	// author queue
	int head, tail;
	head = 0, tail = 1;
	authorIdx[0] = 0;	// Erdos, P. should be processed first
	while(head!=tail)
	{
		ci = &cooperation[authorIdx[head++]];
		s = ci->coauthor.size();
		for(i=0; i<s; i++)
		{
			ci2 = &cooperation[ci->coauthor[i]];
			if(ci2->erdosNum==-1)
			{
				ci2->erdosNum = ci->erdosNum+1;
				authorIdx[tail++] = ci->coauthor[i];
			}
		}
	}
}

int main()
{
	int i, j, k, s, t;
	int p, n;
	int scenarioNum;
	char name[NAMESIZE];
	char temp[LINELENGTH];
	vector<int> authorIdx;
	map<string, int>::iterator pos;
	authorIdx.reserve(20);
	bool flag;
	scanf("%d", &scenarioNum);
	for(s=0; s<scenarioNum; s++)
	{
		scanf("%d%d", &p, &n);
		if(p==0)
			break;
		nameSet["Erdos, P."] = 0;
		cooperation[0].erdosNum = 0;
		cooperation[0].coauthor.clear();
		t = 1;
		// input the article database
		for(i=0; i<p; i++)
		{
			// parse the author list
			flag = false;
			while(true)
			{
				scanf("%s", name);
				strcat(name, " ");
				scanf("%s", temp);
				j = strlen(temp);
				if(temp[j-1]==':' || temp[j-1]!=':' && temp[j-1]!=',')	// strange format in the test data set...
					flag = true;
				if(temp[j-1]==',' || temp[j-1]==':')
					temp[j-1] = 0;
				strcat(name, temp);
				pos = nameSet.find(name);
				if(pos==nameSet.end())	// check if this name has already been seen
				{
					nameSet[name] = t;
					cooperation[t].erdosNum = -1;
					cooperation[t].coauthor.clear();
					authorIdx.push_back(t);
					t++;
				}
				else
				{
					authorIdx.push_back(nameSet[name]);
				}
				if(flag)
				{
					fgets(temp, sizeof(temp), stdin);
					temp[strlen(temp)-1] = 0;
					break;
				}
			}
			// establish the cooperation relationship
			for(j=0; j<authorIdx.size()-1; j++)
			{
				for(k=j+1; k<authorIdx.size(); k++)
				{
					cooperation[authorIdx[j]].coauthor.push_back(authorIdx[k]);
					cooperation[authorIdx[k]].coauthor.push_back(authorIdx[j]);
				}
			}
			authorIdx.clear();
		}
		// calculate erdos numbers
		calcErdosNum();
		// 
		printf("Scenario %d\n", s+1);
		for(i=0; i<n; i++)
		{
			fgets(name, sizeof(name), stdin);
			name[strlen(name)-1] = 0;
			printf("%s ", name);
			pos = nameSet.find(name);
			if(pos!=nameSet.end())
				k = cooperation[nameSet[name]].erdosNum;
			else
				k = -1;
			if(k!=-1)
				printf("%d\n", k);
			else
				printf("infinity\n");
		}
		// clear
		nameSet.clear();
	}
	return 0;
}
