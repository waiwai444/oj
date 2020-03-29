#include <stdio.h>
#include <string.h>
#include <math.h>
#include <map>
#include <string>

#define MAX_CITY 100
#define INF 0x3f3f3f3f

const double pi = 3.141592653589793;
const int R = 6378;
struct CityInfo
{
	int id;
	double lat, lon;
};
int n, m, q;
std::map<std::string, CityInfo> city_map;
int adj_mat[MAX_CITY][MAX_CITY];

inline double distance(double lat1, double lon1, double lat2, double lon2)
{
	return R*acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
}

inline int round_pos(double x)
{
	return (int)(x+0.5);
}

void floyd()
{
	int i, j, k, t;
	for(k = 0; k < n; k++)
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				t = adj_mat[i][k] + adj_mat[k][j];
				if(adj_mat[i][j] > t)
					adj_mat[i][j] = t;
			}
		}
	}
}

int main()
{
	int i, test_case;
	char name[25], name2[25];
	CityInfo city;
	test_case = 0;
	while(scanf("%d%d%d", &n, &m, &q) != EOF && n)
	{
		for(i = 0; i < n; i++)
		{
			city.id = i;
			scanf("%s%lf%lf", name, &city.lat, &city.lon);
			city.lat = city.lat*pi/180;
			city.lon = city.lon*pi/180;
			city_map[name] = city;
		}
		memset(adj_mat, INF, sizeof(adj_mat));
		for(i = 0; i < m; i++)
		{
			scanf("%s%s", name, name2);
			CityInfo& city1 = city_map[name];
			CityInfo& city2 = city_map[name2];
			adj_mat[city1.id][city2.id] = round_pos(distance(city1.lat, city1.lon, city2.lat, city2.lon));
		}
		floyd();
		if(++test_case > 1)
			printf("\n");
		printf("Case #%d\n", test_case);
		for(i = 0; i < q; i++)
		{
			scanf("%s%s", name, name2);
			CityInfo& city1 = city_map[name];
			CityInfo& city2 = city_map[name2];
			if(adj_mat[city1.id][city2.id] >= INF)
				printf("no route exists\n");
			else
				printf("%d km\n", adj_mat[city1.id][city2.id]);
		}
	}
	return 0;
}
