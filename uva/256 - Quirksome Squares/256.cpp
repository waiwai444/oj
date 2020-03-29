#include <cstdio>

int sq[10000];
const int base[4] = {10, 100, 1000, 10000};

int main()
{
    int i, j, n;
    for(i = 0; i <= 9999; ++i)
        sq[i] = i*i;
    while(std::scanf("%d", &n) != EOF)
    {
        j = n/2-1;
        int m = base[j]*base[j];
        for(i = 0; i <= 9999 && sq[i] < m; ++i)
        {
            if(sq[i]/base[j]+sq[i]%base[j] == i)
                std::printf("%0*d\n", n, sq[i]);
        }
    }
    return 0;
}
