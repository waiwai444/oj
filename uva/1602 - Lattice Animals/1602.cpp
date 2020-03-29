#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

struct polyomino_t
{
    int n, h, w;
    std::pair<int, int> pos[10];
    int hash;
};

std::map<int, std::vector<std::vector<polyomino_t> > > res[11];

void rotate(polyomino_t &p)
{
    for(int i = 0; i < p.n; ++i)
    {
        int t = p.pos[i].first;
        p.pos[i].first = -p.pos[i].second+p.w-1;
        p.pos[i].second = t;
    }
    std::sort(&p.pos[0], &p.pos[p.n]);
    std::swap(p.h, p.w);
}

void turn_h(polyomino_t &p)
{
    for(int i = 0; i < p.n; ++i)
        p.pos[i].second = p.w-p.pos[i].second-1;
    std::sort(&p.pos[0], &p.pos[p.n]);
}

void turn_v(polyomino_t &p)
{
    for(int i = 0; i < p.n; ++i)
        p.pos[i].first = p.h-p.pos[i].first-1;
    std::sort(&p.pos[0], &p.pos[p.n]);
}

bool same(const polyomino_t &p, const polyomino_t &q)
{
    return std::equal(&p.pos[0], &p.pos[p.n], &q.pos[0]);
}

void add_square(polyomino_t &p, int r, int c)
{
    p.pos[p.n].first = r, p.pos[p.n].second = c;
    ++p.n;
    if(r < 0)
        for(int i = 0; i < p.n; ++i)
            ++p.pos[i].first;
    else if(c < 0)
        for(int i = 0; i < p.n; ++i)
            ++p.pos[i].second;
    if(r < 0 || r >= p.h)
        ++p.h;
    else if(c < 0 || c >= p.w)
        ++p.w;
    for(int i = 0; i < p.n-1; ++i)
    {
        int t = std::abs(p.pos[i].first-p.pos[p.n-1].first)+std::abs(p.pos[i].second-p.pos[p.n-1].second);
        p.hash += t*t;
    }
    std::sort(&p.pos[0], &p.pos[p.n]);
    if(p.h < p.w)
        rotate(p);
}

void check_and_add(polyomino_t &p)
{
    int i, j;
    std::vector<std::vector<polyomino_t> > &poly = res[p.n][p.hash];
    for(i = 0; i < poly.size(); ++i)
    {
        std::vector<polyomino_t> &var = poly[i];
        if(var[0].h != p.h || var[0].w != p.w || p.hash != var[0].hash)
            continue;
        for(j = 0; j < var.size(); ++j)
            if(same(p, var[j]))
                break;
        if(j < var.size())
            break;
    }
    if(i == poly.size())
    {
        poly.push_back(std::vector<polyomino_t>());
        std::vector<polyomino_t> &var = poly.back();
        if(p.h*p.w == p.n)
            var.push_back(p);
        else if(p.h == p.w)
        {
            for(i = 0; i < 4; ++i)
            {
                var.push_back(p);
                if(i&1)
                    turn_h(p);
                else
                    turn_v(p);
                var.push_back(p);
                rotate(p);
            }
        }
        else
        {
            var.push_back(p);
            turn_h(p);
            var.push_back(p);
            turn_v(p);
            var.push_back(p);
            turn_h(p);
            var.push_back(p);
        }
    }
}

void solve()
{
    int i, j, k;
    polyomino_t p;
    char lattice[10][10];

    std::memset(&p, 0, sizeof(p));
    p.n = p.h = p.w = 1;
    res[1][p.hash] = std::vector<std::vector<polyomino_t> >(1, std::vector<polyomino_t>(1, p));
    for(i = 2; i <= 10; ++i)
    {
        std::map<int, std::vector<std::vector<polyomino_t> > >::iterator it;
        for(it = res[i-1].begin(); it != res[i-1].end(); ++it)
        {
            for(j = 0; j < it->second.size(); ++j)
            {
                std::memset(lattice, 0, sizeof(lattice));
                polyomino_t &q = it->second[j][0];
                for(k = 0; k < q.n; ++k)
                    lattice[q.pos[k].first][q.pos[k].second] = 1;
                for(k = 0; k < q.n; ++k)
                {
                    int r = q.pos[k].first, c = q.pos[k].second;
                    if(lattice[r][c] == 0)
                        continue;
                    if(r > 0 && lattice[r-1][c] == 0 || r == 0)
                    {
                        add_square(p = q, r-1, c);
                        check_and_add(p);
                    }
                    if(lattice[r+1][c] == 0)
                    {
                        add_square(p = q, r+1, c);
                        check_and_add(p);
                    }
                    if(c > 0 && lattice[r][c-1] == 0 || c == 0)
                    {
                        add_square(p = q, r, c-1);
                        check_and_add(p);
                    }
                    if(lattice[r][c+1] == 0)
                    {
                        add_square(p = q, r, c+1);
                        check_and_add(p);
                    }
                }
            }
        }
    }
}

int main()
{
    int i, n, w, h;
    solve();
    while(std::scanf("%d%d%d", &n, &w, &h) != EOF)
    {
        int ans = 0;
        std::map<int, std::vector<std::vector<polyomino_t> > >::iterator it;
        for(it = res[n].begin(); it != res[n].end(); ++it)
            for(i = 0; i < it->second.size(); ++i)
                if(it->second[i][0].w <= w && it->second[i][0].h <= h || it->second[i][0].w <= h && it->second[i][0].h <= w)
                    ++ans;
        std::printf("%d\n", ans);
    }
    return 0;
}
