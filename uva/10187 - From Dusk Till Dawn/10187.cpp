#include <stdio.h>
#include <string.h>
#include <map>
#include <string>

struct RouteSpec
{
	int to_city;
	int depart_time;
	int travel_time;
};

struct CityGraph
{
	RouteSpec route[100][100];
	int nout[100];
	int ncities;
};

std::map<std::string, int> city_map;
CityGraph city_graph;
int source, target;

int arrive_day[100];
int arrive_time[100];
bool processed[100];

void get_test_case()
{
	int nroutes;
	char fcity_name[32], tcity_name[32];
	int dtime, ttime;
	std::map<std::string, int>::iterator it;
	std::string city_name;
	scanf("%d", &nroutes);
	while(nroutes-- > 0)
	{
		scanf("%s%s%d%d", fcity_name, tcity_name, &dtime, &ttime);
		if(dtime >= 6 && dtime < 18 || (dtime + ttime) % 24 > 6 && (dtime + ttime) % 24 <= 18 || ttime > 12)
			continue;
		int fcity, tcity;
		city_name = fcity_name;
		it = city_map.find(city_name);
		if(it == city_map.end())
		{
			fcity = city_graph.ncities;
			city_map.insert(it, std::map<std::string, int>::value_type(city_name, city_graph.ncities++));
		}
		else
			fcity = it->second;
		city_name = tcity_name;
		it = city_map.find(city_name);
		if(it == city_map.end())
		{
			tcity = city_graph.ncities;
			city_map.insert(it, std::map<std::string, int>::value_type(city_name, city_graph.ncities++));
		}
		else
			tcity = it->second;
		int& nout = city_graph.nout[fcity];
		city_graph.route[fcity][nout].to_city = tcity;
		if(dtime >= 18)
			city_graph.route[fcity][nout].depart_time = dtime - 18;	// take 18:00 as the beginning of a day
		else
			city_graph.route[fcity][nout].depart_time = dtime + 6;
		city_graph.route[fcity][nout].travel_time = ttime;
		++nout;
	}
	scanf("%s%s", fcity_name, tcity_name);
	source = target = -1;
	it = city_map.find(fcity_name);
	if(it != city_map.end())
		source = it->second;
	it = city_map.find(tcity_name);
	if(it != city_map.end())
		target = it->second;
}

void clear()
{
	city_map.clear();
	for(int i = 0; i < city_graph.ncities; i++)
		city_graph.nout[i] = 0;
	city_graph.ncities = 0;
}

int earlist_arrive_day()
{
	int i, j;
	memset(arrive_day, 1, city_graph.ncities * sizeof(int));
	memset(arrive_time, 1, city_graph.ncities * sizeof(int));
	memset(processed, false, city_graph.ncities * sizeof(bool));
	arrive_day[source] = arrive_time[source] = 0;
	int current_city;
	int earlist_day, earlist_time;
	for(i = 1; i < city_graph.ncities; ++i)
	{
		current_city = -1;
		earlist_day = earlist_time = 200;
		for(j = 0; j < city_graph.ncities; ++j)
		{
			if(!processed[j] && (arrive_day[j] < earlist_day || arrive_day[j] == earlist_day && arrive_time[j] < earlist_time))
			{
				earlist_day = arrive_day[j];
				earlist_time = arrive_time[j];
				current_city = j;
			}
		}
		if(current_city == -1)
			break;
		for(j = 0; j < city_graph.nout[current_city]; ++j)
		{
			const RouteSpec& route = city_graph.route[current_city][j];
			if(!processed[route.to_city])
			{
				if(route.depart_time >= arrive_time[current_city] && (arrive_day[current_city] < arrive_day[route.to_city] || route.depart_time + route.travel_time < arrive_time[route.to_city]))	// go in the same day
				{					
					arrive_day[route.to_city] = arrive_day[current_city];
					arrive_time[route.to_city] = route.depart_time + route.travel_time;
				}
				else if(route.depart_time < arrive_time[current_city] && arrive_day[current_city] < arrive_day[route.to_city] && route.depart_time + route.travel_time < arrive_time[route.to_city])	// go in the next day
				{
					arrive_day[route.to_city] = arrive_day[current_city] + 1;
					arrive_time[route.to_city] = route.depart_time + route.travel_time;
				}
			}
		}
		processed[current_city] = true;
	}
	return arrive_day[target];
}

int main()
{
	int i;
	int test_case;
	scanf("%d", &test_case);
	for(i = 1; i <= test_case; i++)
	{
		get_test_case();
		printf("Test Case %d.\n", i);
		if(source == -1 || target == -1)
			printf("There is no route Vladimir can take.\n");
		else
		{
			int day = earlist_arrive_day();
			if(day == 0x01010101)
				printf("There is no route Vladimir can take.\n");
			else
				printf("Vladimir needs %d litre(s) of blood.\n", day);
		}
		clear();
	}
	return 0;
}
