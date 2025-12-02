#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <tuple>
#include <vector>

int main()
{
    int a, b, c, d;
    std::vector<std::tuple<int, int, int, int>> ans;
    ans.reserve(500);
    for(b = 2; b <= 138; ++b)
        for(c = b; c < 200; ++c)
            for(d = c; d < 200; ++d)
            {
                int r = b*b*b+c*c*c+d*d*d;
                if(r > 200*200*200)
                    break;
                a = pow(r, 1/3.0)+0.1;
                if(a*a*a == r)
                    ans.push_back(std::make_tuple(a, b, c, d));
            }
    std::sort(ans.begin(), ans.end());
    for(auto &t : ans)
        printf("Cube = %d, Triple = (%d,%d,%d)\n", std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t));
    return 0;
}
