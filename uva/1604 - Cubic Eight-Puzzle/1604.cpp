#include <cstdio>
#include <cstring>
#include <queue>

#define EMPTY 0
#define BRW 1
#define BWR 2
#define RBW 3
#define RWB 4
#define WBR 5
#define WRB 6

const int rotate_v[7] = {EMPTY, RBW, WBR, BRW, WRB, BWR, RWB};
const int rotate_h[7] = {EMPTY, WRB, RWB, WBR, BWR, RBW, BRW};
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

char init[3][3], target[256][3][3];
int ri, ci, rt, ct;
char hash[15116544];

int get_hash(char conf[][3])
{
    int i, j, h = 0, e;
    for(i = 0; i < 3; ++i)
    {
        for(j = 0; j < 3; ++j)
        {
            if(conf[i][j] > 0)
                h = h*6+conf[i][j]-1;
            else
                e = i*3+j;
        }
    }
    return e*1679616+h;
}

void get_init_conf()
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(i == ri && j == ci)
                init[i][j] = EMPTY;
            else
                init[i][j] = WRB;
        }
    }
}

void get_target_recur(int r, int c, char arr[][3], int *n, char conf[][3])
{
    static const int tab[4][2] = {{EMPTY, EMPTY}, {BRW, BWR}, {RBW, RWB}, {WBR, WRB}};
    if(c > 2)
        ++r, c = 0;
    if(r > 2)
    {
        std::memcpy(target[(*n)++], conf, 9);
        return;
    }
    char ch = arr[r][c];
    if(ch == 0)
    {
        conf[r][c] = EMPTY;
        get_target_recur(r, c+1, arr, n, conf);
    }
    else
    {
        for(int i = 0; i < 2; ++i)
        {
            conf[r][c] = tab[ch][i];
            get_target_recur(r, c+1, arr, n, conf);
        }
    }
}

void get_target_conf()
{
    int n = 0;
    char ch[2], arr[3][3], conf[3][3];
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::scanf("%s", ch);
            switch(ch[0])
            {
            case 'E':
                arr[i][j] = 0, rt = i, ct = j; break;
            case 'B':
                arr[i][j] = 1; break;
            case 'R':
                arr[i][j] = 2; break;
            case 'W':
                arr[i][j] = 3; break;
            }
        }
    }
    get_target_recur(0, 0, arr, &n, conf);
}

void move(char conf[][3], int r, int c, int r2, int c2)
{
    int color;
    if(r != r2)
        color = rotate_v[conf[r][c]];
    else
        color = rotate_h[conf[r][c]];
    conf[r2][c2] = color;
    conf[r][c] = EMPTY;
}

struct rec_t
{
    char conf[3][3];
    char re, ce, step;

    rec_t(char conf[][3], char re, char ce, char step)
        : re(re), ce(ce), step(step)
    { std::memcpy(this->conf, conf, 9); }
};

int bfs(std::queue<rec_t> *q, int dir)
{
    int cur_step = q->front().step;
    while(q->front().step == cur_step)
    {
        rec_t r = q->front();
        q->pop();
        for(int i = 0; i < 4; ++i)
        {
            int re2 = r.re+dr[i], ce2 = r.ce+dc[i];
            if(re2 >= 0 && re2 <= 2 && ce2 >= 0 && ce2 <= 2)
            {
                char conf2[3][3];
                std::memcpy(conf2, r.conf, 9);
                move(conf2, re2, ce2, r.re, r.ce);
                int h = get_hash(conf2);
                if(hash[h] == dir)
                    continue;
                hash[h] |= dir;
                if(hash[h] > dir)
                    return r.step+1;
                q->push(rec_t(conf2, re2, ce2, r.step+1));
            }
        }
    }
    return -1;
}

int solve()
{
    int step, max_step1, max_step2;
    std::queue<rec_t> q1, q2;

    std::memset(hash, 0, sizeof(hash));

    q1.push(rec_t(init, ri, ci, 0));
    hash[get_hash(init)] |= 1;
    for(int i = 0; i < 256; ++i)
    {
        if(std::memcmp(target[i], init, 9) == 0)
            return 0;
        q2.push(rec_t(target[i], rt, ct, 0));
        hash[get_hash(target[i])] |= 2;
    }

    for(int i = 0; i < 8; ++i)
    {
        step = bfs(&q1, 1);
        if(step >= 0)
            return step;
    }

    max_step1 = 8, max_step2 = 0;
    while(!q1.empty() && !q2.empty() && max_step1+max_step2 < 30)
    {
        step = bfs(&q1, 1);
        if(step >= 0)
            return step+max_step2;
        ++max_step1;
        step = bfs(&q2, 2);
        if(step >= 0)
            return step+max_step1;
        ++max_step2;
    }
    return -1;
}

int main()
{
    int r, c, ans;
    while(std::scanf("%d%d", &r, &c) != EOF)
    {
        if(r == 0 && c == 0)
            break;
        ri = c-1, ci = r-1;
        get_init_conf();
        get_target_conf();
        ans = solve();
        std::printf("%d\n", ans);
    }
    return 0;
}
