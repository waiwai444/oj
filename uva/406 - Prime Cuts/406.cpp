#include <algorithm>
#include <cstdio>
#include <vector>

char is_prime[1001];
std::vector<int> prime_list;
int idx[1001];

void init()
{
    int i, j;
    for(i = 1; i < 1000; i += 2)
        is_prime[i] = 1;
    is_prime[2] = 1;
    for(i = 3; i < 1000; i += 2)
        if(is_prime[i])
            for(j = i+i; j < 1000; j += i)
                is_prime[j] = 0;
    prime_list.push_back(1);
    prime_list.push_back(2);
    for(i = 3; i < 1000; i += 2)
        if(is_prime[i])
            prime_list.push_back(i);
    for(i = 1, j = 0; i <= 1000; ++i)
    {
        if(i == prime_list[j+1])
            ++j;
        idx[i] = j;
    }
}

int main()
{
    int i, j, n, c;
    init();
    while(std::scanf("%d%d", &n, &c) != EOF)
    {
        j = idx[n];
        std::printf("%d %d:", n, c);
        int l = std::max(j/2-(c-1), 0);
        int r = j-l+1;
        for(i = l; i < r; ++i)
            std::printf(" %d", prime_list[i]);
        std::printf("\n\n");
    }
    return 0;
}
