#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility>

char line[512];
char frm[5][5];

int main()
{
    int i, j, re, ce, tc = 0;
    bool fail;
    char *p;
    while(fgets(line, sizeof(line), stdin))
    {
        if(line[0] == 'Z' && !isdigit(line[1]) && line[1] != ' ')
            break;
        for(j = 0; j < 5; j++)
        {
            frm[0][j] = line[j];
            if(line[j] == ' ')
                re = 0, ce = j;
        }
        for(i = 1; i < 5; i++)
        {
            fgets(line, sizeof(line), stdin);
            for(j = 0; j < 5; j++)
            {
                frm[i][j] = line[j];
                if(line[j] == ' ')
                    re = i, ce = j;
            }
        }
        fail = false;
        for(;;)
        {
            fgets(line, sizeof(line), stdin);
            p = line;
            while(*p)
            {
                if(*p == '0')
                    break;
                if(!fail)
                {
                    switch(*p)
                    {
                    case 'A':
                        if(re == 0)
                            fail = true;
                        else
                        {
                            std::swap(frm[re][ce], frm[re-1][ce]);
                            --re;
                        }
                        break;
                    case 'B':
                        if(re == 4)
                            fail = true;
                        else
                        {
                            std::swap(frm[re][ce], frm[re+1][ce]);
                            ++re;
                        }
                        break;
                    case 'R':
                        if(ce == 4)
                            fail = true;
                        else
                        {
                            std::swap(frm[re][ce], frm[re][ce+1]);
                            ++ce;
                        }
                        break;
                    case 'L':
                        if(ce == 0)
                            fail = true;
                        else
                        {
                            std::swap(frm[re][ce], frm[re][ce-1]);
                            --ce;
                        }
                        break;
                    }
                }
                ++p;
            }
            if(*p == '0')
                break;
        }
        if(tc)
            putchar('\n');
        printf("Puzzle #%d:\n", ++tc);
        if(fail)
            printf("This puzzle has no final configuration.\n");
        else
        {
            for(i = 0; i < 5; i++)
            {
                putchar(frm[i][0]);
                for(j = 1; j < 5; j++)
                    putchar(' '), putchar(frm[i][j]);
                putchar('\n');
            }
        }
    }
    return 0;
}

