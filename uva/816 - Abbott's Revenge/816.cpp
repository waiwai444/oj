#include <cstdio>
#include <cstring>

const int N = 0, S = 1, E = 2, W = 3;
const int L = 0, F = 1, R = 2;
const int NEXT_DIR[4][3] = {
    {W, N, E}, // N
    {E, S, W}, // S
    {N, E, S}, // E
    {S, W, N}  // W
};
const int NEXT_STEP[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
const int OPPO_DIR[4] = {S, N, W, E};

struct node_t
{
    char sign[4][3];
    char vis_out[4];
    int in_dir[4]; // the previous in-dir for each out-dir
} board[10][10];

char name[25];
int en_r, en_c, go_r, go_c;
int start_dir;

struct status_t
{
    int r, c;
    int in_dir;
};

status_t q[500];
int front, rear;

inline int get_dir(char d)
{
    switch(d)
    {
    case 'N':
        return N;
    case 'S':
        return S;
    case 'E':
        return E;
    case 'W':
        return W;
    }
    return -1;
}

inline int get_arrow(char a)
{
    switch(a)
    {
    case 'L':
        return L;
    case 'F':
        return F;
    case 'R':
        return R;
    }
    return -1;
}

inline void next_pos(int r, int c, int out_dir, int *next_r, int *next_c)
{
    *next_r = r+NEXT_STEP[out_dir][0];
    *next_c = c+NEXT_STEP[out_dir][1];
}

inline void enqueue(int r, int c, int in_dir)
{
    q[rear].r = r, q[rear].c = c;
    q[rear].in_dir = in_dir;
    ++rear;
}

inline void dequeue(int *r, int *c, int *in_dir)
{
    *r = q[front].r, *c = q[front].c;
    *in_dir = q[front].in_dir;
    ++front;
}

int print_path(int r, int c, int in_dir)
{
    if(r == en_r && c == en_c && in_dir < 0)
    {
        std::printf("  (%d,%d)", r, c);
        return 1;
    }
    int r1, c1, p;
    next_pos(r, c, OPPO_DIR[in_dir], &r1, &c1);
    p = print_path(r1, c1, board[r1][c1].in_dir[in_dir]);
    if(p == 10)
        std::printf("\n  (%d,%d)", r, c);
    else
        std::printf(" (%d,%d)", r, c);
    return ++p > 10 ? 1 : p;
}

void solve()
{
    int i, r, c, r1, c1, in_dir, ai, out_dir;

    front = rear = 0;
    next_pos(en_r, en_c, start_dir, &r1, &c1);
    enqueue(r1, c1, start_dir);
    board[en_r][en_c].vis_out[start_dir] = 1;
    board[en_r][en_c].in_dir[start_dir] = -1;
    while(front < rear)
    {
        dequeue(&r, &c, &in_dir);
        if(r == go_r && c == go_c)
            break;
        node_t &p = board[r][c];
        for(i = L; i <= R; ++i)
        {
            if(!p.sign[in_dir][i])
                continue;
            out_dir = NEXT_DIR[in_dir][i];
            if(p.vis_out[out_dir] == 0)
            {
                next_pos(r, c, out_dir, &r1, &c1);
                enqueue(r1, c1, out_dir);
                p.vis_out[out_dir] = 1;
                p.in_dir[out_dir] = in_dir;
            }
        }
    }

    if(r == go_r && c == go_c)
    {
        print_path(r, c, in_dir);
        std::putchar('\n');
    }
    else
        std::puts("  No Solution Possible");
}

int main()
{
    int i, r, c, dir;
    char str[8];
    while(std::scanf("%s", name))
    {
        if(std::strcmp(name, "END") == 0)
            break;
        std::memset(board, 0, sizeof(board));
        std::scanf("%d%d%s%d%d", &en_r, &en_c, str, &go_r, &go_c);
        start_dir = get_dir(str[0]);
        for(;;)
        {
            std::scanf("%d", &r);
            if(r == 0)
                break;
            std::scanf("%d", &c);
            for(;;)
            {
                std::scanf("%s", str);
                if(str[0] == '*')
                    break;
                dir = get_dir(str[0]);
                for(i = 0; str[i+1] != '\0'; ++i)
                    board[r][c].sign[dir][get_arrow(str[i+1])] = 1;
            }
        }
        std::puts(name);
        solve();
    }
    return 0;
}

