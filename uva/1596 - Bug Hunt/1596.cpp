#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <map>

long arr_sz[52];
std::map<long, long> arr_vals[52];

int get_arr_idx(char name)
{
    if(name >= 'a' && name <= 'z')
        return name-'a';
    return name-'A'+26;
}

bool handle_value(const char *str, long *val)
{
    int a;
    long idx;
    if(isdigit(str[0]))
    {
        *val = atol(str);
        return true;
    }
    a = get_arr_idx(str[0]);
    if(!handle_value(str+2, &idx))
        return false;
    if(idx >= arr_sz[a])
        return false;
    std::map<long, long>::const_iterator it = arr_vals[a].find(idx);
    if(it == arr_vals[a].end())
        return false;
    *val = it->second;
    return true;
}

bool handle_assignee(const char *str, long val)
{
    int a = get_arr_idx(str[0]);
    long idx;
    if(!handle_value(str+2, &idx))
        return false;
    if(idx >= arr_sz[a])
        return false;
    arr_vals[a][idx] = val;
    return true;
}

int main()
{
    int i, a, l, err;
    long val;
    char line[100], *peq;
    for(;;)
    {
        fgets(line, sizeof(line), stdin);
        if(line[0] == '.')
            break;
        memset(arr_sz, -1, sizeof(arr_sz));
        for(i = 0; i < 52; ++i)
            arr_vals[i].clear();
        err = 0, l = 1;
        for(;;)
        {
            if(!err)
            {
                if(peq = strchr(line, '='))
                {
                    if(handle_value(peq+1, &val))
                    {
                        if(!handle_assignee(line, val))
                            err = l;
                    }
                    else
                        err = l;
                }
                else
                {
                    a = get_arr_idx(line[0]);
                    if(arr_sz[a] >= 0)
                        err = l;
                    else
                        arr_sz[a] = atol(line+2);
                }
            }

            fgets(line, sizeof(line), stdin);
            if(line[0] == '.')
                break;
            ++l;
        }
        printf("%d\n", err);
    }
    return 0;
}

