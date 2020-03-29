#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Task {
	int id;
	int day;
	int fine;
};

vector<Task> task;

inline bool cmp(const Task &a, const Task &b)
{
	if(a.day*b.fine<b.day*a.fine)
		return true;
	else
		return false;
}

int main()
{
	int i, d, n;
	task.reserve(1000);
	cin>>d;
	while(d-->0)
	{
		cin>>n;
		task.resize(n);
		for(i=0; i<n; i++)
		{
			task[i].id = i+1;
			cin>>task[i].day;
			cin>>task[i].fine;
		}
		stable_sort(task.begin(), task.end(), cmp);
		for(i=0; i<n; i++)
		{
			cout<<task[i].id;
			if(i<n-1)
				cout<<' ';
			else
				cout<<endl;
		}
		if(d>0)
		{
			task.clear();
			cout<<endl;
		}
	}
	return 0;
}