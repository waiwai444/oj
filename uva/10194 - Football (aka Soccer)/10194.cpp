#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct TeamInfo {
	string name;
	int score;
	int wins;
	int draws;
	int loses;
	int matches;
	int goals;
	int conceded;
public:
	TeamInfo() : score(0), wins(0), draws(0), loses(0), matches(0), goals(0), conceded(0) {}
};

inline bool cmp(const TeamInfo *a, const TeamInfo *b)
{
	if(a->score>b->score)
		return true;
	else if(a->score<b->score)
		return false;
	if(a->wins>b->wins)
		return true;
	else if(a->wins<b->wins)
		return false;
	if(a->goals-a->conceded>b->goals-b->conceded)
		return true;
	else if(a->goals-a->conceded<b->goals-b->conceded)
		return false;
	if(a->goals>b->goals)
		return true;
	else if(a->goals<b->goals)
		return false;
	if(a->matches<b->matches)
		return true;
	else if(a->matches>b->matches)
		return false;
	string name1 = a->name;
	string name2 = b->name;
	for(int i=0; i<name1.size(); i++)
		if(name1[i]>='A' && name1[i]<='Z')
			name1[i] += 32;
	for(int i=0; i<name2.size(); i++)
		if(name2[i]>='A' && name2[i]<='Z')
			name2[i] += 32;
	if(name1<name2)
		return true;
	else
		return false;
}

int main()
{
	int i, n, t, g;
	char line[128];
	map<string, TeamInfo> teams;
	map<string, TeamInfo>::const_iterator iter;
	vector<const TeamInfo *> ranking;
	ranking.reserve(30);
	TeamInfo empty_info;
	string team_name_1;
	string team_name_2;
	int goals1, goals2;
	cin>>n;
	cin.getline(line, 128);
	while(n-->0)
	{
		cin.getline(line, 128);
		cout<<line<<endl;
		cin>>t;
		cin.getline(line, 128);
		for(i=0; i<t; i++)
		{
			cin.getline(line, 128);
			empty_info.name = line;
			teams[empty_info.name] = empty_info;
		}
		cin>>g;
		cin.getline(line, 128);
		for(i=0; i<g; i++)
		{
			cin.getline(line, 128);
			team_name_1 = strtok(line, "#");
			goals1 = atoi(strtok(NULL, "@"));
			goals2 = atoi(strtok(NULL, "#"));
			team_name_2 = strtok(NULL, "\n");
			TeamInfo &info1 = teams[team_name_1];
			TeamInfo &info2 = teams[team_name_2];
			info1.goals += goals1;
			info2.conceded += goals1;
			info1.conceded += goals2;
			info2.goals += goals2;
			info1.matches++;
			info2.matches++;
			if(goals1>goals2)
			{
				info1.score += 3;
				info1.wins++;
				info2.loses++;
			}
			else if(goals1==goals2)
			{
				info1.score += 1;
				info2.score += 1;
				info1.draws++;
				info2.draws++;
			}
			else
			{
				info2.score += 3;
				info2.wins++;
				info1.loses++;
			}
		}
		for(iter=teams.begin(); iter!=teams.end(); iter++)
		{
			ranking.push_back(&(*iter).second);
		}
		sort(ranking.begin(), ranking.end(), cmp);
		for(i=0; i<ranking.size(); i++)
			cout<<i+1<<") "<<ranking[i]->name<<' '<<ranking[i]->score<<"p, "<<ranking[i]->matches<<"g ("<<ranking[i]->wins<<'-'<<ranking[i]->draws<<'-'<<ranking[i]->loses<<"), "<<ranking[i]->goals-ranking[i]->conceded<<"gd ("<<ranking[i]->goals<<'-'<<ranking[i]->conceded<<')'<<endl;
		if(n>0)
		{
			cout<<endl;
			teams.clear();
			ranking.clear();
		}
	}
	return 0;
}