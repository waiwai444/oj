#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<string> dictionary[16];	// dictionary for different lengths
vector<vector<int> > adj_list[16];	// adjacent list for different lengths
vector<int> precedent;

//bool doublet(string str1, string str2)
//{
//	if(str1.length()!=str2.length())
//		return false;
//	int i;
//	int diff = 0;
//	for(i=0; i<str1.length(); i++)
//	{
//		if(str1[i]!=str2[i])
//			diff++;
//	}
//	if(diff==1)
//		return true;
//	return false;
//}

int binarysearch(int dic_idx, string str)
{
	int low, high, mid;
	low = 0;
	high = dictionary[dic_idx].size()-1;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(dictionary[dic_idx][mid]==str)
			return mid;
		else if(dictionary[dic_idx][mid]>str)
			high = mid-1;
		else
			low = mid+1;
	}
	return -1;
}

void construct_graph()
{
	int i, j, d, k, t;
	string str;
	for(i=0; i<16; i++)
	{
		adj_list[i].resize(dictionary[i].size());
		sort(dictionary[i].begin(), dictionary[i].end(), less<string>());
	}
	for(d=0; d<16; d++)
	{
		for(i=0; i<dictionary[d].size(); i++)
		{
			for(j=0; j<=d; j++)
			{
				str = dictionary[d][i];
				for(k=0; k<26; k++)
				{
					if(k<=dictionary[d][i][j]-'a')
						continue;
					str[j] = 'a'+k;
					t = binarysearch(d, str);
					if(t!=-1)
					{
						adj_list[d][i].push_back(t);
						adj_list[d][t].push_back(i);
					}
				}
			}
		}
	}
}

void bfs(int dic_idx, int source, int sink)
{
	int i;
	if(source==sink)
		return;
	int p, r;
	queue<int> Q;
	Q.push(source);
	precedent.resize(dictionary[dic_idx].size());
	for(i=0; i<dictionary[dic_idx].size(); i++)
		precedent[i] = -1;
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		for(i=0; i<adj_list[dic_idx][p].size(); i++)
		{
			r = adj_list[dic_idx][p][i];
			if(r==source || precedent[r]>=0)
				continue;
			precedent[r] = p;
			if(r==sink)
				return;
			Q.push(r);
		}
	}
}

int main()
{
	int i, d;
	int p;
	char line[64];
	vector<int> path;
	string str1, str2;
	for(i=0; i<16; i++)
		dictionary[i].reserve(25143);
	while(cin.getline(line, 64))
	{
		if(line[0]==0)
			break;
		str1 = line;
		dictionary[str1.length()-1].push_back(str1);
	}
	construct_graph();
	int source, sink;
	bool first = true;
	path.reserve(25143);
	precedent.reserve(25143);
	while(cin>>str1>>str2)
	{
		if(!first)
			cout<<endl;
		else
			first = false;
		if(str1.length()!=str2.length())
		{
			cout<<"No solution."<<endl;
			continue;
		}
		path.clear();
		source = sink = -1;
		d = str1.length()-1;
		for(i=0; i<dictionary[d].size(); i++)
		{
			if(str1==dictionary[d][i])
				source = i;
			if(str2==dictionary[d][i])
				sink = i;
			if(source>=0 && sink>=0)
				break;
		}
		bfs(d, source, sink);
		if(source!=sink && precedent[sink]==-1)
		{
			cout<<"No solution."<<endl;
			continue;
		}
		p = sink;
		while(p!=source)
		{
			path.push_back(p);
			p = precedent[p];
		}
		cout<<dictionary[d][source]<<endl;
		for(i=path.size()-1; i>=0; i--)
		{
			cout<<dictionary[d][path[i]]<<endl;
		}
	}
	return 0;
}