#include <algorithm>
#include <stdio.h>
#include <utility>

int n, m;
std::pair<int, int> num[10001];

bool cmp(std::pair<int, int> &p1, std::pair<int, int> &p2)
{
    if(p1.second < p2.second)
        return true;
    if(p1.second > p2.second)
        return false;
    if((p1.first & 1) == 1 && (p2.first & 1) == 0)
        return true;
    if((p1.first & 1) == 0 && (p2.first & 1) == 1)
        return false;
    if(p1.first & 1)
        return p1.first > p2.first;
    return p1.first < p2.first;
}

int main()
{
    int i;
    while(scanf("%d%d", &n, &m))
    {
        if(n == 0)
            break;
        for(i = 0; i < n; ++i)
        {
            scanf("%d", &num[i].first);
            num[i].second = num[i].first % m;
        }
        std::sort(&num[0], &num[n], cmp);
        printf("%d %d\n", n, m);
        for(i = 0; i < n; ++i)
        {
            printf("%d\n", num[i].first);
        }
    }
    printf("0 0\n");
    return 0;
}
