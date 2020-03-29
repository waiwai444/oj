#include <cstdio>

char input[3][5];
const char charset[] = "*0123456789";

bool is_matchable(int val, char *str)
{
    char *p = str;
    while(*p)
        ++p;
    --p;
    while(p >= str && val)
    {
        int d = val%10;
        if(*p != '*' && d != *p-'0')
            return false;
        val /= 10;
        --p;
    }
    return p < str && val == 0;
}

void check_puzzle(int i, int j, int x, int y, int *cnt)
{
    if(i == 2)
    {
        if(is_matchable(x*y, input[2]))
            ++*cnt;
    }
    else if(input[i][j] == 0)
        check_puzzle(i+1, 0, x, y, cnt);
    else
    {
        int x2, y2;
        if(input[i][j] == '*')
        {
            for(int k = (j == 0 ? 1 : 0); k <= 9; ++k)
            {
                i == 0 ? (x2 = x*10+k, y2 = y) : (x2 = x, y2 = y*10+k);
                check_puzzle(i, j+1, x2, y2, cnt);
                if(*cnt >= 2)
                    return;
            }
        }
        else
        {
            i == 0 ? (x2 = x*10+input[i][j]-'0', y2 = y) : (x2 = x, y2 = y*10+input[i][j]-'0');
            check_puzzle(i, j+1, x2, y2, cnt);
        }
    }
}

bool is_good()
{
    int cnt = 0;
    check_puzzle(0, 0, 0, 0, &cnt);
    return cnt == 1;
}

bool dfs(int i, int j, int cur, int max)
{
    if(cur == max)
        return is_good();
    if(input[i][j] == 0)
        ++i, j = 0;
    if(i >= 3)
        return false;
    for(const char *p = charset; *p; ++p)
    {
        if(j == 0 && *p == '0')
            continue;
        if(*p != input[i][j])
        {
            char tmp = input[i][j];
            input[i][j] = *p;
            ++cur;
            if(dfs(i, j+1, cur, max))
                return true;
            --cur;
            input[i][j] = tmp;
        }
        else
        {
            if(dfs(i, j+1, cur, max))
                return true;
        }
    }
    return false;
}

void solve()
{
    if(is_good())
        return;
    for(int i = 1; i <= 8; ++i)
    {
        if(dfs(0, 0, 0, i))
            break;
    }
}

int main()
{
    int tc = 0;
    while(std::scanf("%s", input[0]) != EOF)
    {
        if(input[0][0] == '0')
            break;
        std::scanf("%s%s", input[1], input[2]);
        solve();
        std::printf("Case %d: %s %s %s\n", ++tc, input[0], input[1], input[2]);
    }
    return 0;
}
