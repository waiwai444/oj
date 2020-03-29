#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<string> fragment;

void bubblesort(int fragment_idx[])
{
	int i, j, t;
	bool stop;
	for(i=1; i<fragment.size(); i++)
	{
		stop = true;
		for(j=0; j<fragment.size()-i; j++)
		{
			if(fragment[fragment_idx[j]].length()<fragment[fragment_idx[j+1]].length())
			{
				t = fragment_idx[j], fragment_idx[j] = fragment_idx[j+1], fragment_idx[j+1] = t;
				stop = false;
			}
		}
		if(stop)
			break;
	}
}

struct Bin {
	int len;
	int num;
	string fragment[2];
};

int main()
{
	int i, j, k;
	int d, l, l1, l2;
	char line[2048];
	int fragment_idx[288];
	vector<Bin> bin_set;
	set<string> latent_file;
	set<string> new_latent_file;
	set<string> temp;
	cin>>d;
	cin.getline(line, 2048);
	cin.getline(line, 2048);
	fragment.reserve(288);
	while(d-->0)
	{
		fragment.clear();
		cin.getline(line, 2048);
		while(line[0]!=0)
		{
			fragment.push_back(line);
			cin.getline(line, 2048);
		}
		for(i=0; i<fragment.size(); i++)
		{
			fragment_idx[i] = i;
		}
		bubblesort(fragment_idx);
		Bin bin;
		bin.len = 0;
		bin_set.clear();
		for(i=0; i<fragment.size(); i++)
		{
			if(bin.len!=fragment[fragment_idx[i]].length())
			{
				bin.len = fragment[fragment_idx[i]].length();
				bin.fragment[0] = fragment[fragment_idx[i]];
				bin.num = 1;
				bin_set.push_back(bin);
			}
			else if(bin_set[bin_set.size()-1].num==1 && bin_set[bin_set.size()-1].fragment[0]!=fragment[fragment_idx[i]])
			{
				bin_set[bin_set.size()-1].fragment[1] = fragment[fragment_idx[i]];
				bin_set[bin_set.size()-1].num++;
			}
		}

		if(bin_set.size()==1)	// if all fragments have the same length
		{
			if(bin_set[0].num==1)
				cout<<bin_set[0].fragment[0]<<bin_set[0].fragment[0]<<endl;
			else
				cout<<bin_set[0].fragment[0]<<bin_set[0].fragment[1]<<endl;
			if(d>0)
				cout<<endl;
			continue;
		}
		latent_file.clear();
		l = bin_set.size()-1;
		for(i=0; i<bin_set[0].num; i++)
		{
			if(i==0)
			{
				for(j=0; j<bin_set[l].num; j++)
				{
					latent_file.insert(bin_set[0].fragment[i]+bin_set[l].fragment[j]);
					latent_file.insert(bin_set[l].fragment[j]+bin_set[0].fragment[i]);
				}
			}
			else
			{
				new_latent_file.clear();
				temp.clear();
				for(j=0; j<bin_set[l].num; j++)
				{
					new_latent_file.insert(bin_set[0].fragment[i]+bin_set[l].fragment[j]);
					new_latent_file.insert(bin_set[l].fragment[j]+bin_set[0].fragment[i]);
				}
				set_intersection(latent_file.begin(), latent_file.end(), new_latent_file.begin(), new_latent_file.end(), inserter(temp, temp.end()));
				latent_file = temp;
			}
		}
		for(i=1; i<bin_set.size(); i++)
		{
			if(latent_file.size()==1)
				break;
			l = bin_set.size()-1-i;
			if(i==l)
			{
				new_latent_file.clear();
				temp.clear();
				if(bin_set[i].num==1)
					new_latent_file.insert(bin_set[i].fragment[0]+bin_set[i].fragment[0]);
				else
				{
					new_latent_file.insert(bin_set[i].fragment[0]+bin_set[i].fragment[1]);
					new_latent_file.insert(bin_set[i].fragment[1]+bin_set[i].fragment[0]);
				}
				set_intersection(latent_file.begin(), latent_file.end(), new_latent_file.begin(), new_latent_file.end(), inserter(temp, temp.end()));
				latent_file = temp;
			}
			else
			{
				for(j=0; j<bin_set[i].num; j++)
				{
					new_latent_file.clear();
					temp.clear();
					for(k=0; k<bin_set[l].num; k++)
					{
						new_latent_file.insert(bin_set[i].fragment[j]+bin_set[l].fragment[k]);
						new_latent_file.insert(bin_set[l].fragment[k]+bin_set[i].fragment[j]);
					}
					set_intersection(latent_file.begin(), latent_file.end(), new_latent_file.begin(), new_latent_file.end(), inserter(temp, temp.end()));
					latent_file = temp;
				}
			}
		}
		cout<<*latent_file.begin()<<endl;

		if(d>0)
			cout<<endl;
	}
	return 0;
}