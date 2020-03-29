#include <cstdio>
#include <cstring>

int n, arr[1000], ans;
int aux[1000];

void merge(int a, int m, int b)
{
    int i, j, k;
    std::memcpy(&aux[a], &arr[a], (b-a+1)*sizeof(int));
    i = k = a, j = m+1;
    while(i <= m && j <= b)
    {
        if(aux[i] <= aux[j])
            arr[k++] = aux[i++];
        else
        {
            arr[k++] = aux[j++];
            ans += m-i+1;
        }
    }
    while(i <= m)
        arr[k++] = aux[i++];
    while(j <= b)
        arr[k++] = aux[j++];
}

void merge_sort(int a, int b)
{
    if(a == b)
        return;
    int m = (a+b)/2;
    merge_sort(a, m);
    merge_sort(m+1, b);
    merge(a, m, b);
}

int main()
{
    int i, j;
    while(std::scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        ans = 0;
        merge_sort(0, n-1);
        std::printf("Minimum exchange operations : %d\n", ans);
    }
    return 0;
}
