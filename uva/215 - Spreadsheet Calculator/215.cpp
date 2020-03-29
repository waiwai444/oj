#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <utility>

int row, col;

char expr[20][10][80];
long val[20][10];
char vis[20][10];

std::pair<int, int> convert_pos(char *pos)
{
    return std::make_pair(pos[0]-'A', pos[1]-'0');
}

bool evaluate(int r, int c)
{
    char *ptr = expr[r][c];
    long result = 0;
    bool neg = *ptr == '-';
    if(*ptr == '+' || *ptr == '-')
        ++ptr;
    while(*ptr)
    {
        if(std::isdigit(*ptr))
            result += neg ? -std::strtol(ptr, &ptr, 10) : std::strtol(ptr, &ptr, 10);
        else
        {
            std::pair<int, int> pos = convert_pos(ptr);
            if(expr[pos.first][pos.second][0] != 0)
            {
                if(vis[pos.first][pos.second] == 0)
                {
                    vis[pos.first][pos.second] = 1;
                    bool r = evaluate(pos.first, pos.second);
                    if(!r)
                        return false;
                }
                else
                    return false;
            }
            result += neg ? -val[pos.first][pos.second] : val[pos.first][pos.second];
            ptr += 2;
        }
        if(*ptr)
        {
            neg = (*ptr == '-');
            ++ptr;
        }
    }
    expr[r][c][0] = 0;
    val[r][c] = result;
    return true;
}

bool solve()
{
    int i, j;
    bool valid = true;
    std::memset(vis, 0, sizeof(vis));
    std::memset(val, 0, sizeof(val));
    for(i = 0; i < row; ++i)
    {
        for(j = 0; j < col; ++j)
        {
            if(expr[i][j][0] == 0)
                continue;
            if(vis[i][j] == 0)
            {
                bool r = evaluate(i, j);
                if(!r)
                    valid = false;
            }
        }
    }
    return valid;
}

void print_ans(bool valid)
{
    int i, j;
    if(valid)
    {
        std::putchar(' ');
        for(i = 0; i < col; ++i)
            std::printf("%6d", i);
        std::putchar('\n');
        for(i = 0; i < row; ++i)
        {
            std::putchar('A'+i);
            for(j = 0; j < col; ++j)
                std::printf("%6ld", val[i][j]);
            std::putchar('\n');
        }
    }
    else
    {
        for(i = 0; i < row; ++i)
            for(j = 0; j < col; ++j)
                if(expr[i][j][0])
                    std::printf("%c%c: %s\n", 'A'+i, '0'+j, expr[i][j]);
    }
    std::putchar('\n');
}

int main()
{
    int i, j;
    while(std::scanf("%d%d", &row, &col) != EOF)
    {
        if(row == 0 && col == 0)
            break;
        for(i = 0; i < row; ++i)
            for(j = 0; j < col; ++j)
                std::scanf("%s", expr[i][j]);
        print_ans(solve());
    }
    return 0;
}

