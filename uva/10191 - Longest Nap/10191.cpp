#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct TimeSpan {
	int begin;
	int end;
};

inline bool cmp(TimeSpan span1, TimeSpan span2)
{
	if(span1.begin>span2.begin)
		return false;
	else
		return true;
}

int main()
{
	int i, d, s;
	int longest_nap_begin;
	int longest_nap_span;
	int cur_span;
	char line[256];
	vector<TimeSpan> schedule;
	TimeSpan span;
	schedule.reserve(100);
	d = 1;
	while(cin>>s)
	{
		if(s==0)
		{
			cout<<"Day #"<<(d++)<<": the longest nap starts at 10:00 and will last for 8 hours and 0 minutes."<<endl;
			continue;
		}
		cin.getline(line, 256);
		for(i=0; i<s; i++)
		{
			cin.getline(line, 256);
			span.begin = atoi(strtok(line, ":"))*60+atoi(strtok(NULL, " "));
			span.end = atoi(strtok(NULL, ":"))*60+atoi(strtok(NULL, " "));
			schedule.push_back(span);
		}
		sort(schedule.begin(), schedule.end(), cmp);
		longest_nap_begin = 600;
		longest_nap_span = schedule[0].begin-600;
		for(i=1; i<schedule.size(); i++)
		{
			cur_span = schedule[i].begin-schedule[i-1].end;
			if(cur_span>longest_nap_span)
			{
				longest_nap_begin = schedule[i-1].end;
				longest_nap_span = cur_span;
			}
		}
		cur_span = 1080-schedule[i-1].end;
		if(cur_span>longest_nap_span)
		{
			longest_nap_begin = schedule[i-1].end;
			longest_nap_span = cur_span;
		}
		if(longest_nap_span<60)
			cout<<"Day #"<<(d++)<<": the longest nap starts at "<<longest_nap_begin/60<<":"<<setw(2)<<setfill('0')<<longest_nap_begin%60<<" and will last for "<<longest_nap_span<<" minutes."<<endl;
		else
			cout<<"Day #"<<(d++)<<": the longest nap starts at "<<longest_nap_begin/60<<":"<<setw(2)<<setfill('0')<<longest_nap_begin%60<<" and will last for "<<longest_nap_span/60<<" hours and "<<longest_nap_span%60<<" minutes."<<endl;
		schedule.clear();
	}
	return 0;
}