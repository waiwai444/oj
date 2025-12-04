#include <iostream>
#include <deque>

int n;
int ps[2000001];

int main()
{
    int i, j, a, c;
    std::deque<int> min;
    std::ios_base::sync_with_stdio(false);
    while((std::cin >> n) && n)
    {
        for(i = 1; i <= n; ++i)
        {
            std::cin >> a;
            ps[i] = ps[i-1]+a;
        }
        for(i = 1; i < n; ++i)
            ps[n+i] = ps[n]+ps[i];
        c = 0;
        i = j = 1;
        min.clear();
        while(i <= n)
        {
            for(; j < i+n && ps[j] >= ps[i-1]; ++j)
            {
                while(!min.empty() && ps[min.back()] > ps[j])
                    min.pop_back();
                min.push_back(j);
            }
            if(j == i+n)
            {
                ++c;
                if(++i > min.front())
                    min.pop_front();
                if(!min.empty() && ps[min.front()] < ps[i-1])
                {
                    i = min.front()+1;
                    min.pop_front();
                }
            }
            else
            {
                i = ++j;
                min.clear();
            }
        }
        std::cout << c << '\n';
    }
    return 0;
}
