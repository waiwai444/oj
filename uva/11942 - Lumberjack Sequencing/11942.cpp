#include <cstdio>

int main()
{
    int n, i, arr[10];
    bool ordered, asc;
    std::scanf("%d", &n);
    std::puts("Lumberjacks:");
    while(n--)
    {
        ordered = asc = true;
        std::scanf("%d %d", &arr[0], &arr[1]);
        if(arr[0] > arr[1])
            asc = false;
        for(i = 2; i < 10; ++i)
        {
            std::scanf("%d", &arr[i]);
            if(ordered)
            {
                if(arr[i] > arr[i-1] && !asc)
                    ordered = false;
                else if(arr[i] < arr[i-1] && asc)
                    ordered = false;
            }
        }
        ordered ? std::puts("Ordered") : std::puts("Unordered");
    }
    return 0;
}
