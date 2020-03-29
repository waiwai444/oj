#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 5001

int n;
int xl[MAXN], yl[MAXN], xr[MAXN], yr[MAXN];
int idx[MAXN];
int x[MAXN], y[MAXN];
int *cmp_arr, *cmp_heap_arr;

bool cmp(int i, int j)
{
    return cmp_arr[i] < cmp_arr[j];
}

bool greater(int i, int j)
{
    return cmp_heap_arr[i] > cmp_heap_arr[j];
}

bool put(int *left, int *right, int *res)
{
    int i, cur = 1;

    std::sort(&idx[1], &idx[n+1], cmp);

    std::vector<int> heap;
    for(i = 1; i <= n; ++i)
    {
        while(left[idx[cur]] == i)
        {
            heap.push_back(idx[cur]);
            std::push_heap(heap.begin(), heap.end(), greater);
            ++cur;
        }
        if(heap.empty())
            return false;
        std::pop_heap(heap.begin(), heap.end(), greater);
        if(right[heap.back()] < i)
            return false;
        res[heap.back()] = i;
        heap.pop_back();
    }

    return true;
}

int main()
{
    int i;
    while(1)
    {
        scanf("%d", &n);
        if (n == 0)
            break;
        for(i = 1; i <= n; ++i)
        {
            scanf("%d%d%d%d", &xl[i], &yl[i], &xr[i], &yr[i]);
            idx[i] = i;
        }
        bool suc = false;
        cmp_arr = xl, cmp_heap_arr = xr;
        if(put(xl, xr, x))
        {
            cmp_arr = yl, cmp_heap_arr = yr;
            if(put(yl, yr, y))
            {
                for(i = 1; i <= n; ++i)
                    printf("%d %d\n", x[i], y[i]);
                suc = true;
            }
        }
        if(!suc)
            puts("IMPOSSIBLE");
    }
    return 0;
}
