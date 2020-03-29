#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#define EPS 1e-6

struct map_t
{
    std::string name;
    double left, right, upper, lower;
    double area;
    double cx, cy;
    double ar;
};

struct location_t
{
    double x, y;
    std::vector<int> midx;
    bool p;
};

std::vector<map_t> maps;
std::map<std::string, location_t> locs;

bool cmp_maps(const map_t &m1, const map_t &m2)
{
    return m1.area > m2.area;
}

bool in_map(const map_t &m, double x, double y)
{
    return m.left <= x && m.right >= x && m.upper >= y && m.lower <= y;
}

double sq_dist(double x1, double y1, double x2, double y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

void find_maps(location_t &loc)
{
    int i = 0, j, k;
    while(i < maps.size())
    {
        if(in_map(maps[i], loc.x, loc.y))
        {
            k = i;
            for(j = i+1; j < maps.size(); ++j)
            {
                if(maps[j].area != maps[i].area)
                    break;
                if(!in_map(maps[j], loc.x, loc.y))
                    continue;
                double d1 = sq_dist(maps[i].cx, maps[i].cy, loc.x, loc.y);
                double d2 = sq_dist(maps[j].cx, maps[j].cy, loc.x, loc.y);
                if(d2 < d1-EPS)
                    k = j;
                else if(d2 > d1+EPS)
                    continue;
                d1 = fabs(maps[i].ar-0.75);
                d2 = fabs(maps[j].ar-0.75);
                if(d2 < d1-EPS)
                    k = j;
                else if(d2 > d1+EPS)
                    continue;
                d1 = sq_dist(maps[i].right, maps[i].lower, loc.x, loc.y);
                d2 = sq_dist(maps[j].right, maps[j].lower, loc.x, loc.y);
                if(d2 > d1+EPS)
                    k = j;
                else if(d2 < d1-EPS)
                    continue;
                if(maps[j].left < maps[i].left)
                    k = j;
            }
            loc.midx.push_back(k);
            i = j;
        }
        else
            ++i;
    }
    loc.p = true;
}

int main()
{
    int l;
    std::string line, name;
    std::istringstream iss;
    std::map<std::string, location_t>::iterator it;
    map_t map;
    location_t loc;
    std::ios_base::sync_with_stdio(false);
    std::getline(std::cin, line);
    for(;;)
    {
        std::getline(std::cin, line);
        if(line == "LOCATIONS")
            break;
        iss.clear(), iss.str(line);
        iss >> map.name >> map.left >> map.upper >> map.right >> map.lower;
        if(map.left > map.right)
            std::swap(map.left, map.right);
        if(map.lower > map.upper)
            std::swap(map.lower, map.upper);
        map.area = (map.upper-map.lower)*(map.right-map.left);
        map.cx = (map.left+map.right)/2.0;
        map.cy = (map.upper+map.lower)/2.0;
        map.ar = (map.upper-map.lower)/(map.right-map.left);
        maps.push_back(map);
    }
    std::sort(maps.begin(), maps.end(), cmp_maps);
    loc.p = false;
    for(;;)
    {
        std::getline(std::cin, line);
        if(line == "REQUESTS")
            break;
        iss.clear(), iss.str(line);
        iss >> name >> loc.x >> loc.y;
        locs[name] = loc;
    }
    for(;;)
    {
        std::getline(std::cin, line);
        if(line == "END")
            break;
        iss.clear(), iss.str(line);
        iss >> name >> l;
        std::cout << name << " at detail level " << l;
        it = locs.find(name);
        if(it == locs.end())
            std::cout << " unknown location\n";
        else
        {
            if(!it->second.p)
                find_maps(it->second);
            if(it->second.midx.size() == 0)
                std::cout << " no map contains that location\n";
            else if(it->second.midx.size() < l)
                std::cout << " no map at that detail level; using "
                          << maps[it->second.midx.back()].name << '\n';
            else
                std::cout << " using " << maps[it->second.midx[l-1]].name << '\n';
        }
    }
    return 0;
}

