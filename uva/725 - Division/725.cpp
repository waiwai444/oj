#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<int, int> > ans[81];

void solve()
{
    int n, d, q;
    char dig[10] = { 1, 2, 3, 4, 6, 0, 5, 7, 8, 9 };
    while(std::next_permutation(dig, dig+10))
    {
        n = dig[0]*10000+dig[1]*1000+dig[2]*100+dig[3]*10+dig[4];
        d = dig[5]*10000+dig[6]*1000+dig[7]*100+dig[8]*10+dig[9];
        if(n%d)
            continue;
        if((q = n/d) <= 80)
            ans[q].push_back(std::make_pair(n, d));
    }
}

void print_ans(int N)
{
    int i;
    for(i = 0; i < ans[N].size(); ++i)
        std::printf("%05d / %05d = %d\n", ans[N][i].first, ans[N][i].second, N);
    if(ans[N].size() == 0)
        std::printf("There are no solutions for %d.\n", N);
}

int main()
{
    int N;
    int tc = 0;
    solve();
    while(std::scanf("%d", &N), N)
    {
        if(tc++)
            std::putchar('\n');
        print_ans(N);
    }
    return 0;
}

