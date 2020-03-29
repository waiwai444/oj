#include <stdio.h>

int n;
int array[5];
int map_num;

inline void swap(int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void dfs(int cur_depth, int depth_bound)
{
    int i;
    for(i = 0; i < n-1; i++)
    {
        if(array[i] > array[i+1])
        {
            swap(i, i+1);
            if(cur_depth+1 < depth_bound)
                dfs(cur_depth+1, depth_bound);
            else
                map_num++;
            swap(i, i+1);
        }
    }
}

int main()
{
    int i, j, inv, tc = 0;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
            scanf("%d", &array[i]);
        
        inv = 0;
        for(i = 0; i < n; i++)
            for(j = i+1; j < n; j++)
                if(array[j] < array[i])
                    inv++;
        
        map_num = 0;
        dfs(0, inv);
        
        printf("There are %d swap maps for input data set %d.\n", map_num, ++tc);
    }
    return 0;
}