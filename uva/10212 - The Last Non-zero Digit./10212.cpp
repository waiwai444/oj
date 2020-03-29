#include <cstdio>

const int pow2[] = { 2, 4, 8, 6 };
const int pow3[] = { 3, 9, 7, 1 };
const int pow7[] = { 7, 9, 3, 1 };
const int pow9[] = { 9, 1 };

int count25(int n, int d)
{
    if(n <= 1)
        return 0;
    return n/d+count25(n/d, d);
}

int count_odd(int n, int d)
{
    if(n <= 1)
        return 0;
    return n/10+(n%10 >= d)+count_odd(n/5, d);
}

int count(int n, int d)
{
    if(n <= 1)
        return 0;
    return count(n/2, d)+count_odd(n, d);
}

int solve(int n, int m)
{
    int p2, p5, d3, d7, d9, ans = 1;
    p2 = count25(n, 2)-count25(n-m, 2);
    p5 = count25(n, 5)-count25(n-m, 5);
    d3 = count(n, 3)-count(n-m, 3);
    d7 = count(n, 7)-count(n-m, 7);
    d9 = count(n, 9)-count(n-m, 9);
    if(d3)
        ans *= pow3[(d3-1)%4];
    if(d7)
        ans *= pow7[(d7-1)%4];
    if(d9)
        ans *= pow9[(d9-1)%2];
    if(p2 > p5)
        ans *= pow2[(p2-p5-1)%4];
    else if(p2 < p5)
        ans *= 5;
    return ans%10;
}

int main()
{
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
        printf("%d\n", solve(n, m));
    return 0;
}

