#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct PhotoRecord {
	int time;
	char in_out;
	int loc;
};

inline bool cmp(const PhotoRecord &a, const PhotoRecord &b)
{
	if(a.time<b.time)
		return true;
	else
		return false;
}

int main()
{
	int i, d;
	int fare[24];
	char line[128];
	map<string, vector<PhotoRecord> > records;
	string license_num;
	PhotoRecord rec;
	cin>>d;
	while(d-->0)
	{
		for(i=0; i<24; i++)
			cin>>fare[i];
		cin.getline(line, 128);
		while(cin.getline(line, 128))
		{
			if(line[0]==0)
				break;
			license_num = strtok(line, " ");
			strtok(NULL, ":");
			rec.time = (atoi(strtok(NULL, ":"))-1)*1440+atoi(strtok(NULL, ":"))*60+atoi(strtok(NULL, " "));
			if(strcmp(strtok(NULL, " "), "enter")==0)
				rec.in_out = 'i';
			else
				rec.in_out = 'o';
			rec.loc = atoi(strtok(NULL, " "));
			records[license_num].push_back(rec);
		}
		map<string, vector<PhotoRecord> >::iterator iter;
		int hour;
		int toll;
		cout.setf(ios::fixed);
		for(iter=records.begin(); iter!=records.end(); ++iter)
		{
			vector<PhotoRecord> &vec = (*iter).second;
			sort(vec.begin(), vec.end(), cmp);
			toll = 0;
			for(i=0 ;i<vec.size()-1; i++)
			{
				if(vec[i].in_out!='i')
					continue;
				if(vec[i+1].in_out!='o')
					continue;
				hour = vec[i].time/60%24;
				if(vec[i].loc<vec[i+1].loc)
					toll += (vec[i+1].loc-vec[i].loc)*fare[hour];
				else
					toll += (vec[i].loc-vec[i+1].loc)*fare[hour];
				toll += 100;
				i++;
			}
			if(toll>0)
			{
				toll += 200;
				cout<<(*iter).first<<" $"<<setprecision(2)<<toll/100.0<<endl;
			}
		}
		if(d>0)
		{
			cout<<endl;
			records.clear();
		}
	}
	return 0;
}