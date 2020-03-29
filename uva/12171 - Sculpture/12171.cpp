#include <cstdio>
#include <cstring>
#include <queue>

int n;
const int D[6][3] = {
    {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
};

struct box_t
{
    int x0, y0, z0;
    int x, y, z;
} boxes[50];

long area, vol;
int cx[1001], cy[1001], cz[1001];
int rx[105], ry[105], rz[105], mx, my, mz;
char grid[105][105][105];

struct cell_t
{
    int x, y, z;
};

std::queue<cell_t> q;

inline long get_vol(int x, int y, int z)
{
    return (long)(rx[x+1]-rx[x])*(ry[y+1]-ry[y])*(rz[z+1]-rz[z]);
}

inline long get_area(int x, int y, int z, int d)
{
    long dx = rx[x+1]-rx[x], dy = ry[y+1]-ry[y], dz = rz[z+1]-rz[z];
    return d == 0 || d == 1 ? dy*dz : d == 2 || d == 3 ? dx*dz : dx*dy;
}

void floodfill()
{
    int i;
    cell_t p, p1;
    grid[0][0][0] = -1;
    p.x = p.y = p.z = 0;
    q.push(p);
    while(!q.empty())
    {
        p = q.front(), q.pop();
        vol += get_vol(p.x, p.y, p.z);
        for(i = 0; i < 6; ++i)
        {
            p1.x = p.x+D[i][0], p1.y = p.y+D[i][1], p1.z = p.z+D[i][2];
            if(p1.x < 0 || p1.x >= mx || p1.y < 0 || p1.y >= my || p1.z < 0 || p1.z >= mz)
                continue;
            if(grid[p1.x][p1.y][p1.z] == 0)
            {
                grid[p1.x][p1.y][p1.z] = -1;
                q.push(p1);
            }
            else if(grid[p1.x][p1.y][p1.z] == 1)
            {
                area += get_area(p1.x, p1.y, p1.z, i);
            }
        }
    }
}

void solve()
{
    int i, j, k;
    area = 0, vol = 0;
    std::memset(cx, 0, sizeof(cx));
    std::memset(cy, 0, sizeof(cy));
    std::memset(cz, 0, sizeof(cz));
    std::memset(grid, 0, sizeof(grid));
    for(i = 0; i < n; ++i)
    {
        box_t &b = boxes[i];
        cx[b.x0] = cx[b.x0+b.x] = 1;
        cy[b.y0] = cy[b.y0+b.y] = 1;
        cz[b.z0] = cz[b.z0+b.z] = 1;
    }
    for(i = 1, mx = my = mz = 1; i <= 1000; ++i)
    {
        if(cx[i])
            cx[i] = mx, rx[mx] = i, ++mx;
        if(cy[i])
            cy[i] = my, ry[my] = i, ++my;
        if(cz[i])
            cz[i] = mz, rz[mz] = i, ++mz;
    }
    rx[mx] = ry[my] = rz[mz] = 1001;
    for(i = 0; i < n; ++i)
    {
        box_t &b = boxes[i];
        for(j = cy[b.y0]; j <= cy[b.y0+b.y]-1; ++j)
            for(k = cz[b.z0]; k <= cz[b.z0+b.z]-1; ++k)
                grid[cx[b.x0]][j][k] = grid[cx[b.x0+b.x]-1][j][k] = 1;
        for(j = cx[b.x0]; j <= cx[b.x0+b.x]-1; ++j)
            for(k = cz[b.z0]; k <= cz[b.z0+b.z]-1; ++k)
                grid[j][cy[b.y0]][k] = grid[j][cy[b.y0+b.y]-1][k] = 1;
        for(j = cx[b.x0]; j <= cx[b.x0+b.x]-1; ++j)
            for(k = cy[b.y0]; k <= cy[b.y0+b.y]-1; ++k)
                grid[j][k][cz[b.z0]] = grid[j][k][cz[b.z0+b.z]-1] = 1;
    }
    floodfill();
    vol = 1001*1001*1001-vol;
}

int main()
{
    int i, tc;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d", &n);
        for(i = 0; i < n; ++i)
            std::scanf("%d%d%d%d%d%d", &boxes[i].x0, &boxes[i].y0, &boxes[i].z0,
                    &boxes[i].x, &boxes[i].y, &boxes[i].z);
        solve();
        std::printf("%ld %ld\n", area, vol);
    }
    return 0;
}

