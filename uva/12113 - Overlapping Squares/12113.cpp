#include <cstdio>
#include <cstring>

char cell[4][4];
char covered[4][4];

bool finished()
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            if(cell[i][j] != 0)
                return false;
    return true;
}

bool top_piece(int r, int c)
{
    unsigned int mask = 42645;
    if(covered[r][c])
        mask &= ~0xf;
    if(covered[r][c+1])
        mask &= ~(0xf<<4);
    if(covered[r+1][c])
        mask &= ~(0xf<<8);
    if(covered[r+1][c+1])
        mask &= ~(0xf<<12);
    if(r > 0)
    {
        if(covered[r-1][c])
            mask &= ~0x1;
        if(covered[r-1][c+1])
            mask &= ~(0x1<<4);
    }
    if(r < 2)
    {
        if(covered[r+2][c])
            mask &= ~(0x2<<8);
        if(covered[r+2][c+1])
            mask &= ~(0x2<<12);
    }
    if(c > 0)
    {
        if(covered[r][c-1])
            mask &= ~0x4;
        if(covered[r+1][c-1])
            mask &= ~(0x4<<8);
    }
    if(c < 2)
    {
        if(covered[r][c+2])
            mask &= ~(0x8<<4);
        if(covered[r+1][c+2])
            mask &= ~(0x8<<12);
    }
    unsigned int flag = cell[r][c];
    flag |= cell[r][c+1]<<4;
    flag |= cell[r+1][c]<<8;
    flag |= cell[r+1][c+1]<<12;
    return flag && flag == mask;
}

void uncover(int r, int c)
{
    if(!covered[r][c])
    {
        if(r > 0)
            cell[r-1][c] &= ~0x2;
        if(c > 0)
            cell[r][c-1] &= ~0x8;
    }
    if(!covered[r][c+1])
    {
        if(r > 0)
            cell[r-1][c+1] &= ~0x2;
        if(c < 2)
            cell[r][c+2] &= ~0x4;
    }
    if(!covered[r+1][c])
    {
        if(r < 2)
            cell[r+2][c] &= ~0x1;
        if(c > 0)
            cell[r+1][c-1] &= ~0x8;
    }
    if(!covered[r+1][c+1])
    {
        if(r < 2)
            cell[r+2][c+1] &= ~0x1;
        if(c < 2)
            cell[r+1][c+2] &= ~0x4;
    }
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            cell[r+i][c+j] = 0;
            covered[r+i][c+j] = 1;
        }
    }
}

bool solve()
{
    int i, j, k;
    if(finished())
        return false;
    std::memset(covered, 0, sizeof(covered));
    for(k = 0; k < 6; ++k)
    {
        for(i = 0; i < 3; ++i)
        {
            for(j = 0; j < 3; ++j)
                if(top_piece(i, j))
                    break;
            if(j < 3)
                break;
        }
        if(i < 3)
            uncover(i, j);
        else
            return false;
        if(finished())
            return true;
    }
    return false;
}

bool parse_input_line(int num, char *line)
{
    for(int i = 0; i < 9; ++i)
    {
        if(line[i] == '_')
        {
            if((i&1) == 0)
                return false;
            if(num > 0)
                cell[num-1][i/2] |= 2;
            if(num < 4)
                cell[num][i/2] |= 1;
        }
        else if(line[i] == '|')
        {
            if((i&1) == 1 || num == 0)
                return false;
            if(i > 0)
                cell[num-1][i/2-1] |= 8;
            if(i < 8)
                cell[num-1][i/2] |= 4;
        }
    }
    return true;
}

int main()
{
    int i, tc = 0;
    bool ans;
    char line[12];
    while(std::fgets(line, sizeof(line), stdin))
    {
        if(line[0] == '0')
            break;
        std::memset(cell, 0, sizeof(cell));
        ans = parse_input_line(0, line);
        for(i = 1; i < 5; ++i)
        {
            std::fgets(line, sizeof(line), stdin);
            if(ans)
                ans = parse_input_line(i, line);
        }
        if(ans)
            ans = solve();
        std::printf("Case %d: %s\n", ++tc, ans ? "Yes" : "No");
    }
    return 0;
}
