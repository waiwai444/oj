#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

struct Component
{
	int price, quality;
};

int n, b;
int type_num;
std::vector<Component> comp_set[1000];
int top[1000];

bool cmp_q(const Component &c1, const Component &c2)
{
	if(c1.quality < c2.quality)
		return false;
	if(c1.quality > c2.quality)
		return true;
	return c1.price < c2.price;
}

void remove_useless_component(std::vector<Component> &vec)
{
	int i, j, price = vec[0].price, quality = vec[0].quality;
	for(i = j = 1; i < vec.size(); i++)
	{
		if(vec[i].quality < quality && vec[i].price < price)
		{
			vec[j++] = vec[i];
			price = vec[i].price;
			quality = vec[i].quality;
		}
	}
	while(vec.size() > j)
		vec.pop_back();
}

int get_current_cost()
{
	int cost = 0;
	for(int i = 0; i < type_num; i++)
		cost += comp_set[i][top[i]].price;
	return cost;
}

int get_current_quality()
{
	int quality = comp_set[0][top[0]].quality;
	for(int i = 1; i < type_num; i++)
		if(comp_set[i][top[i]].quality < quality)
			quality = comp_set[i][top[i]].quality;
	return quality;
}

int find_largest_second_quality(int *t)
{
	int i = 0;
	while(comp_set[i].size() == top[i]+1)
		i++;
	int quality = comp_set[i][top[i]+1].quality;
	*t = i;
	for(i++; i < type_num; i++)
	{
		if(comp_set[i].size() > top[i]+1 && comp_set[i][top[i]+1].quality > quality)
		{
			quality = comp_set[i][top[i]+1].quality;
			*t = i;
		}
	}
	return quality;
}

int main()
{
	int i, tc;
	char type[21];
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &n, &b);
		type_num = 0;
		std::map<std::string, std::vector<Component> *> type_idx;
		for(i = 0; i < n; i++)
		{
			Component comp;
			scanf("%s%*s%d%d", type, &comp.price, &comp.quality);
			std::map<std::string, std::vector<Component> *>::iterator it = type_idx.find(type);
			if(it == type_idx.end())
			{
				comp_set[type_num].clear();
				it = type_idx.insert(std::make_pair(std::string(type), &comp_set[type_num])).first;
				type_num++;
			}
			it->second->push_back(comp);
		}
		
		for(i = 0; i < type_num; i++)
		{
			std::sort(comp_set[i].begin(), comp_set[i].end(), cmp_q);			
			remove_useless_component(comp_set[i]);
			top[i] = 0;
		}
		
		int cost, quality = get_current_quality(), k;
		for(i = 0; i < type_num; i++)
			while(comp_set[i].size() > top[i]+1 && comp_set[i][top[i]+1].quality >= quality)
				top[i]++;
		cost = get_current_cost();
		while(cost > b)
		{
			quality = find_largest_second_quality(&k);
			cost -= comp_set[k][top[k]].price;
			top[k]++;
			cost += comp_set[k][top[k]].price;
		}
		
		printf("%d\n", quality);
	}
	return 0;
}
