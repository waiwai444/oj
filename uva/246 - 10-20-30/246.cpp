#include <cstdio>
#include <cstring>
#include <deque>
#include <set>
#include <string>

std::deque<int> deck;
std::deque<int> pile[7];
std::set<std::string> vis;

int cur_pile;
int step_cnt;

enum res_e { WIN, LOSS, DRAW } res;

bool is_10_20_30(int x, int y, int z)
{
    return x+y+z == 10 || x+y+z == 20 || x+y+z == 30;
}

std::string make_repr()
{
    std::string str;
    std::deque<int>::iterator it;
    str.reserve(70);
    for(it = deck.begin(); it != deck.end(); ++it)
        str.push_back(*it);
    str.push_back(0);
    for(int i = 0; i < 7; ++i)
    {
        for(it = pile[i].begin(); it != pile[i].end(); ++it)
            str.push_back(*it);
        str.push_back(0);
    }
    str.push_back(cur_pile);
    return str;
}

void play()
{
    int i, x, y, z, empty_cnt = 0;

    for(i = 0; i < 7; ++i)
    {
        pile[i].push_back(deck.front());
        deck.pop_front();
    }

    vis.clear();

    cur_pile = 0;
    step_cnt = 7;
    for(;;)
    {
        z = deck.front(), deck.pop_front();
        std::deque<int> &cp = pile[cur_pile];
        cp.push_back(z);
        while(cp.size() >= 3)
        {
            x = cp.front();
            y = cp[1];
            z = cp.back();
            if(is_10_20_30(x, y, z))
            {
                cp.pop_front();
                cp.pop_front();
                cp.pop_back();
            }
            else
            {
                y = cp[cp.size()-2];
                if(is_10_20_30(x, y, z))
                {
                    cp.pop_front();
                    cp.pop_back();
                    cp.pop_back();
                }
                else
                {
                    x = cp[cp.size()-3];
                    if(is_10_20_30(x, y, z))
                    {
                        cp.pop_back();
                        cp.pop_back();
                        cp.pop_back();
                    }
                    else
                        break;
                }
            }
            deck.push_back(x);
            deck.push_back(y);
            deck.push_back(z);
            if(cp.size() == 0)
                ++empty_cnt;
        }
        ++step_cnt;
        if(empty_cnt == 7)
        {
            res = WIN;
            return;
        }
        if(deck.size() == 0)
        {
            res = LOSS;
            return;
        }
        std::string repr = make_repr();
        if(!vis.insert(repr).second)
        {
            res = DRAW;
            return;
        }
        cur_pile = cur_pile < 6 ? cur_pile+1 : 0;
        while(pile[cur_pile].size() == 0)
            cur_pile = cur_pile < 6 ? cur_pile+1 : 0;
    }
}

int main()
{
    int i, v;
    while(std::scanf("%d", &v))
    {
        if(v == 0)
            break;
        deck.clear();
        for(i = 0; i < 7; ++i)
            pile[i].clear();
        deck.push_back(v);
        for(i = 1; i < 52; ++i)
        {
            std::scanf("%d", &v);
            deck.push_back(v);
        }

        play();

        if(res == WIN)
            std::printf("Win : %d\n", step_cnt);
        else if(res == LOSS)
            std::printf("Loss: %d\n", step_cnt);
        else if(res == DRAW)
            std::printf("Draw: %d\n", step_cnt);
    }
    return 0;
}

