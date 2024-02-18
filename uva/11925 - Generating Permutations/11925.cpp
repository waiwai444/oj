#include <algorithm>
#include <stdio.h>
#include <string>
#include <utility>

int n;
int perm[300];
int fst, snd;
std::string ops;

void op1()
{
    std::swap(perm[fst], perm[snd]);
    ops.push_back('1');
}

void op2r()
{
    --fst;
    if(fst < 0)
        fst = n-1;
    ops.push_back('2');
}

void solve()
{
    int i, a;
    fst = 0;
    ops.clear();
    for(i = 1; i < n; ++i)
    {
        a = n-i;
        do
        {
            op2r();
            snd = fst+1;
            if(snd == n)
                snd = 0;
            if(perm[fst] > perm[snd])
                op1();
            if(perm[snd] == snd || snd == 0 && perm[0] == n)
                --a;
        }
        while(fst > i);
        while(fst > 1)
            op2r();
        if(a == 0)
            break;
        if(i < n-1)
            op2r();
    }
    std::reverse(ops.begin(), ops.end());
    printf("%s\n", ops.c_str());
}

int main()
{
    int i;
    ops.reserve(2*300*300+1);
    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;
        for(i = 0; i < n; ++i)
            scanf("%d", &perm[i]);
        solve();
    }
    return 0;
}