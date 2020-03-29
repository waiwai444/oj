#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int seq[][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};

int init[24], fc;
std::vector<int> steps;

void move(int *bd, int s)
{
    int t = bd[seq[s][0]];
    for(int i = 0; i < 6; ++i)
        bd[seq[s][i]] = bd[seq[s][i+1]];
    bd[seq[s][6]] = t;
}

bool finished(int *bd)
{
     if(bd[6] == bd[7] && bd[6] == bd[8] && bd[6] == bd[12]
        && bd[6] == bd[17] && bd[6] == bd[16]
        && bd[6] == bd[15] && bd[6] == bd[11])
     {
         fc = bd[6];
         return true;
     }
     return false;
}

int min_steps(int *bd)
{
    int cnt[4];
    cnt[1] = cnt[2] = cnt[3] = 0;
    ++cnt[bd[6]], ++cnt[bd[7]], ++cnt[bd[8]];
    ++cnt[bd[11]], ++cnt[bd[12]], ++cnt[bd[15]];
    ++cnt[bd[16]], ++cnt[bd[17]];
    return 8-std::max(cnt[1], std::max(cnt[2], cnt[3]));
}

bool dfs(int *cur, int maxd)
{
    int next[24];
    for(int i = 0; i < 8; ++i)
    {
        std::memcpy(next, cur, sizeof(next));
        move(next, i);
        if(min_steps(next) > maxd-steps.size()-1)
            continue;
        steps.push_back(i);
        if(steps.size() == maxd)
        {
            if(finished(next))
                return true;
        }
        else
        {
            if(dfs(next, maxd))
                return true;
        }
        steps.pop_back();
    }
    return false;
}

void iddfs()
{
    int maxd = 1;
    steps.clear();
    if(finished(init))
        return;
    for(;;)
    {
        if(dfs(init, maxd))
            break;
        ++maxd;
    }
}

int main()
{
    int i;
    for(;;)
    {
        std::scanf("%d", &init[0]);
        if(init[0] == 0)
            break;
        for(i = 1; i < 24; ++i)
            std::scanf("%d", &init[i]);
        iddfs();
        if(steps.size() == 0)
            std::puts("No moves needed");
        else
        {
            for(i = 0; i < steps.size(); ++i)
                std::putchar('A'+steps[i]);
            std::putchar('\n');
        }
        std::printf("%d\n", fc);
    }
    return 0;
}
