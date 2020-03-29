#include <stdio.h>
#include <string.h>

#define STRAIGHT_FLUSH 0
#define FOUR_OF_A_KIND 1
#define FULL_HOUSE 2
#define FLUSH 3
#define STRAIGHT 4
#define THREE_OF_A_KIND 5
#define TWO_PAIRS 6
#define ONE_PAIR 7
#define HIGHEST_CARD 8
#define UNKNOWN 9

const char output[9][16] = {
    "straight-flush",
    "four-of-a-kind",
    "full-house",
    "flush",
    "straight",
    "three-of-a-kind",
    "two-pairs",
    "one-pair",
    "highest-card"
};

struct Hand
{
    char card[5][3];
} init, deck;

inline int suit_index(char suit)
{
    if(suit == 'C')
        return 0;
    if(suit == 'D')
        return 1;
    if(suit == 'H')
        return 2;
    return 3;
}

inline int to_value(char ch)
{
    if(ch >= '1' && ch <= '9')
        return ch-'0';
    if(ch == 'T')
        return 10;
    if(ch == 'J')
        return 11;
    if(ch == 'Q')
        return 12;
    if(ch == 'K')
        return 13;
    return 1;
}

void count_value(const Hand &hand, int value_count[])
{
    int i;
    memset(value_count, 0, 14*sizeof(int));
    for(i = 0; i < 5; i++)
        value_count[to_value(hand.card[i][0])]++;
}

int count_pairs(const int value_count[])
{
    int count = 0;
    for(int i = 1; i < 14; i++)
        if(value_count[i] == 2)
        {
            count++;
            if(count == 2)
                return count;
        }
    return count;
}

bool highest_card(const int value_count[])
{
    return value_count[13] > 0;
}

bool one_pair(const int value_count[])
{
    return count_pairs(value_count) == 1;
}

bool two_pairs(const int value_count[])
{
    return count_pairs(value_count) == 2;
}

bool three_of_a_kind(const int value_count[])
{
    for(int i = 1; i < 14; i++)
        if(value_count[i] == 3)
            return true;
    return false;
}

bool straight(const int value_count[])
{
    int continuous_count = 0;
    for(int i = 1; i < 14; i++)
    {
        if(value_count[i] == 1)
        {
            continuous_count++;
            if(continuous_count == 5)
                break;
        }
        else if(value_count[i] > 1)
            return false;
        else
            continuous_count = 0;
    }
    if(continuous_count == 5 || (continuous_count == 4 && value_count[1] == 1))
        return true;
    return false;
}

bool flush(const Hand &hand)
{
    char suit = hand.card[0][1];
    for(int i = 1; i < 5; i++)
        if(hand.card[i][1] != suit)
            return false;
    return true;
}

bool full_house(const int value_count[])
{
    bool three = false, two = false;
    for(int i = 1; i < 14; i++)
        if(value_count[i] == 3)
            three = true;
        else if(value_count[i] == 2)
            two = true;
    return three && two;
}

bool four_of_a_kind(int value_count[])
{
    for(int i = 1; i < 14; i++)
        if(value_count[i] == 4)
            return true;
    return false;
}

bool straight_flush(const Hand &hand, int value_count[])
{
    if(!flush(hand))
        return false;
    return straight(value_count);
}

int dfs(const Hand &hand, int cur_sub, int deck_top)
{
    int i, res(UNKNOWN), temp;
    int value_count[14];
    count_value(hand, value_count);
    Hand new_hand;
    if(straight_flush(hand, value_count))
        res = STRAIGHT_FLUSH;
    else if(four_of_a_kind(value_count))
        res = FOUR_OF_A_KIND;
    else if(full_house(value_count))
        res = FULL_HOUSE;
    else if(flush(hand))
        res = FLUSH;
    else if(straight(value_count))
        res = STRAIGHT;
    else if(three_of_a_kind(value_count))
        res = THREE_OF_A_KIND;
    else if(two_pairs(value_count))
        res = TWO_PAIRS;
    else if(one_pair(value_count))
        res = ONE_PAIR;
    else if(highest_card(value_count))
        res = HIGHEST_CARD;
    for(i = cur_sub; i < 5; i++)
    {
        new_hand = hand;
        new_hand.card[i][0] = deck.card[deck_top][0];
        new_hand.card[i][1] = deck.card[deck_top][1];
        temp = dfs(new_hand, i+1, deck_top+1);
        if(temp < res)
            res = temp;
    }
    return res;
}

int main()
{
    int i, result;
    while(scanf("%s", init.card[0]) != EOF)
    {
        printf("Hand: %s ", init.card[0]);
        for(i = 1; i < 5; i++)
        {
            scanf("%s", init.card[i]);
            printf("%s ", init.card[i]);
        }
        printf("Deck: ");
        for(i = 0; i < 5; i++)
        {
            scanf("%s", deck.card[i]);
            printf("%s ", deck.card[i]);
        }
        result = dfs(init, 0, 0);
        printf("Best hand: %s\n", output[result]);
    }
    return 0;
}