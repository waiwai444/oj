#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <string>

#define HASH_BUCKET 1001

int n, m;
struct col_t
{
    char str[10000][81];
    std::vector<int> row[10000];
    std::map<std::string, int> idx[HASH_BUCKET];
    int nd;
} col[10];
int data[10][10000];
int prev[10000];

int bkdr_hash(const char *str)
{
    static int seed = 131;
    unsigned long h = 0;
    while(*str)
        h = h*seed+(*str++);
    return h%HASH_BUCKET;
}

int store_str(const char *str, int r, int c)
{
    int i, h;
    h = bkdr_hash(str);
    std::map<std::string, int>::iterator it = col[c].idx[h].find(str);
    if(it == col[c].idx[h].end())
    {
        i = col[c].nd++;
        strcpy(col[c].str[i], str);
        col[c].row[i].clear();
        col[c].idx[h][str] = i;
    }
    else
        i = it->second;
    col[c].row[i].push_back(r);
    return i;
}

void solve()
{
    int i, j, k, l;
    memset(prev, -1, sizeof(prev));
    for(i = 1; i < m; ++i)
    {
        for(j = 0; j < col[i].nd; ++j)
        {
            if(col[i].row[j].size() <= 1)
                continue;
            for(k = 0; k < i; ++k)
            {
                for(l = 0; l < col[i].row[j].size(); ++l)
                {
                    if(prev[data[k][col[i].row[j][l]]] >= 0)
                    {
                        printf("NO\n%d %d\n%d %d\n", prev[data[k][col[i].row[j][l]]]+1, col[i].row[j][l]+1, k+1, i+1);
                        return;
                    }
                    prev[data[k][col[i].row[j][l]]] = col[i].row[j][l];
                }
                for(l = 0; l < col[i].row[j].size(); ++l)
                    prev[data[k][col[i].row[j][l]]] = -1;
            }
        }
    }
    printf("YES\n");
}

int main()
{
    int i, j;
    char line[90];
    while(scanf("%d%d", &n, &m) != EOF)
    {
        fgets(line, sizeof(line), stdin);
        for(i = 0; i < m; ++i)
        {
            col[i].nd = 0;
            for(j = 0; j < HASH_BUCKET; ++j)
                col[i].idx[j].clear();
        }
        for(i = 0; i < n; ++i)
        {
            fgets(line, sizeof(line), stdin);
            data[0][i] = store_str(strtok(line, ",\n\r"), i, 0);
            for(j = 1; j < m; ++j)
                data[j][i] = store_str(strtok(NULL, ",\n\r"), i, j);
        }
        solve();
    }
    return 0;
}

