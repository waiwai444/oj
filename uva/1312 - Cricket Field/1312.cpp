#include <algorithm>
#include <stdio.h>

int N, W, H;
int X[302], Y[302];

int idx[302];

bool cmp(int i, int j)
{
    return X[i] < X[j];
}

void solve()
{
    int i, j, P = 0, Q = 0, L = 1;

    if(N == 0)
    {
        printf("0 0 %d\n", W < H ? W : H);
        return;
    }

    for(i = 0; i < N; ++i)
        X[N + i] = W, Y[N + i] = Y[i];
    for(i = 0; i < N; ++i)
        X[2 * N + i] = W, Y[2 * N + i] = Y[i] - 1;
    X[3 * N] = W, Y[3 * N] = H - 1;
    X[3 * N + 1] = 0, Y[3 * N + 1] = 0;
    for(i = 0; i < 3 * N + 2; ++i)
        idx[i] = i;
    N = 3 * N + 2;
    std::sort(&idx[0], &idx[N], cmp);
    for(i = 0; i < N; ++i)
    {
        int x = X[idx[i]], y = Y[idx[i]];
        int a = 0, b = H, c;
        if(x == 0 || y == 0 || y == H)
            continue;
        for(j = i - 1; j >= 0; --j)
        {
            int x2 = X[idx[j]], y2 = Y[idx[j]];
            if(x2 == x)
                continue;
            c = x - x2;
            if(c > b - a)
                c = b - a;
            if(c > L)
            {
                L = c;
                P = x - c;
                Q = a <= y - c + 1 ? y - c + 1 : a;
            }
            if(y2 >= y && y2 < b)
                b = y2;
            if(y2 <= y && y2 > a)
                a = y2;
            if(b - a <= x - x2)
                break;
        }
    }
    printf("%d %d %d\n", P, Q, L);
}

int main()
{
    int i, j, x, y, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d%d", &N, &W, &H);
        for(i = j = 0; i < N; ++i)
        {
            scanf("%d%d", &x, &y);
            if(x == 0 || y == 0 || x == W || y == H)
                continue;
            X[j] = x;
            Y[j++] = y;
        }
        N = j;
        solve();
        if(tc)
            printf("\n");
    }
    return 0;
}
