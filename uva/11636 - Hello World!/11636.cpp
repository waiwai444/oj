#include <cstdio>

const int pow[] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384
};

int main()
{
    int i, n, tc = 0;
    while(std::scanf("%d", &n) != EOF && n >= 0)
    {
        for(i = 0; i <= 14; ++i)
            if(pow[i] >= n)
                break;
        std::printf("Case %d: %d\n", ++tc, i);
    }
    return 0;
}
