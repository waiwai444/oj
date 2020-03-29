#include <cstdio>

int main()
{
    int n, x, sum, max;
    while(std::scanf("%d", &n), n)
    {
        max = sum = 0;
        while(n--)
        {
            std::scanf("%d", &x);
            sum += x;
            if(sum <= 0)
                sum = 0;
            else
            {
                if(sum > max)
                    max = sum;
            }
        }
        if(max > 0)
            std::printf("The maximum winning streak is %d.\n", max);
        else
            std::puts("Losing streak.");
    }
    return 0;
}
