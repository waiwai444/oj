#include <cstdio>
#include <vector>

std::vector<char> fib[5001];

void get_all_fib()
{
    int i, c, n, t;
    fib[0].push_back(0);
    fib[1].push_back(1);
    for(n = 2; n <= 5000; ++n)
    {
        std::vector<char> &x = fib[n-2], &y = fib[n-1], &r = fib[n];
        r.reserve(y.size()+1);
        c = 0;
        for(i = 0; i < x.size(); ++i)
        {
            t = x[i]+y[i]+c;
            if(t >= 10)
            {
                t -= 10;
                c = 1;
            }
            else
                c = 0;
            r.push_back(t);
        }
        if(i < y.size())
            r.push_back(y[i]+c);
        else if(c)
            r.push_back(c);
    }
}

int main()
{
    int n;
    get_all_fib();
    while(std::scanf("%d", &n) != EOF)
    {
        std::printf("The Fibonacci number for %d is ", n);
        for(int i = fib[n].size()-1; i >= 0; --i)
            std::putchar(fib[n][i]+'0');
        std::putchar('\n');
    }
    return 0;
}
