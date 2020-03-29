#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define EPS 1e-8
#define INF 999999

double total;
double pct[144];
int np;
struct player_info_t
{
    char name[21];
    long rd[4], total2, total4;
    bool amat, tie;
    int place;
    double prize;
} player[144];

bool cmp_player2(const player_info_t &p1, const player_info_t &p2)
{
    if(p1.total2 == p2.total2)
        return strcmp(p1.name, p2.name) < 0;
    return p1.total2 < p2.total2;
}

bool cmp_player4(const player_info_t &p1, const player_info_t &p2)
{
    if(p1.total4 == p2.total4)
        return strcmp(p1.name, p2.name) < 0;
    return p1.total4 < p2.total4;
}

bool is_amateur_name(const char *name)
{
    const char *p = &name[19];
    while(p > name && *p == ' ')
        --p;
    return *p == '*';
}

int main()
{
    int i, j, k, l, tc, place;
    char line[50], *p, tmp[5];
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%lf", &total);
        for(i = 0; i < 70; ++i)
            scanf("%lf", &pct[i]);
        scanf("%d", &np);
        fgets(line, sizeof(line), stdin);
        for(i = k = 0; i < np; ++i)
        {
            fgets(line, sizeof(line), stdin);
            strncpy(player[k].name, line, 20);
            player[k].name[20] = '\0';
            player[k].amat = is_amateur_name(player[k].name);
            p = strtok(&line[20], " \n\r");
            for(j = 0; j < 4; ++j)
            {
                if(p[0] == 'D')
                {
                    player[k].rd[j] = INF;
                    break;
                }
                else
                    player[k].rd[j] = atol(p);
                p = strtok(NULL, " \n\r");
            }
            for(++j; j < 4; ++j)
                player[k].rd[j] = INF;
            player[k].total2 = player[k].rd[0]+player[k].rd[1];
            player[k].total4 = player[k].total2+player[k].rd[2]+player[k].rd[3];
            if(player[k].total2 < INF)
                ++k;
        }
        np = k;

        std::sort(&player[0], &player[np], cmp_player2);

        if(np > 70)
        {
            for(i = 70; i < np; ++i)
                if(player[i].total2 != player[i-1].total2)
                    break;
            np = i;
        }

        std::sort(&player[0], &player[np], cmp_player4);

        i = k = l = 0;
        while(i < np)
        {
            if(player[i].total4 >= INF)
                break;
            double q = 0.0;
            for(j = i; j < np && player[j].total4 == player[i].total4; ++j)
            {
                player[j].place = i+1;
                player[j].prize = -1.0;
                player[j].tie = false;
                if(!player[j].amat)
                    q += pct[l++];
            }
            if(k < 70 && k < l)
            {
                bool tie = j-i > 1 && l-k > 1;
                q = total*q/(l-k)/100;
                for(; i < j; ++i)
                {
                    if(!player[i].amat)
                    {
                        player[i].prize = q;
                        player[i].tie = tie;
                    }
                }
            }
            i = j, k = l;
        }
        while(i < np)
            player[i++].place = -1;

        puts("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won");
        puts("-----------------------------------------------------------------------");
        for(i = 0; i < np; ++i)
        {
            printf("%20s ", player[i].name);
            if(player[i].place > 0)
            {
                sprintf(tmp, "%d%c", player[i].place, player[i].tie ? 'T' : ' ');
                printf("%-5s     ", tmp);
            }
            else
                printf("          ");
            printf("%-3ld  %-3ld  ", player[i].rd[0], player[i].rd[1]);
            for(j = 2; j <= 3; ++j)
                if(player[i].rd[j] < INF)
                    printf("%-3ld  ", player[i].rd[j]);
                else
                    printf("     ");
            if(player[i].total4 < INF)
            {
                if(!player[i].amat && player[i].prize >= 0)
                    printf("%-5ld     $%9.2f\n", player[i].total4, player[i].prize+EPS);
                else
                    printf("%ld\n", player[i].total4);
            }
            else
                printf("DQ\n");
        }
        if(tc)
            putchar('\n');
    }
    return 0;
}

