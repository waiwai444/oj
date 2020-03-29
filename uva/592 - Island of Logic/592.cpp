#include <stdio.h>
#include <string.h>

enum StatementType { SELF, OTHER, ENVIR };
enum Description { DIVINE, HUMAN, EVIL, LYING, DAY, NIGHT, UNKNOWN, MULTI };
char description_str[][8] = { "divine", "human", "evil", "lying", "day", "night" };

struct Statement
{
    StatementType type;
    int refer_to;
    Description desc;
    bool neg;
};

int statement_num[5];
Statement statement[5][50];

Description result[5], candidate[5];
Description result_envir, candidate_envir;

bool check_statement_type1(int speaker, int s_idx)  // I am [not] ( divine | human | evil | lying ).
{
    Statement& ss = statement[speaker][s_idx];
    
    if(candidate[speaker] == DIVINE || (candidate[speaker] == HUMAN && candidate_envir == DAY)) // tell truth
    {
        if(!ss.neg)
        {
            if(ss.desc != candidate[speaker])
                return false;
        }
        else
        {
            if(ss.desc == candidate[speaker])
                return false;
        }
    }
    else    // lie
    {
        if(!ss.neg)
        {
            if(ss.desc == candidate[speaker] || ss.desc == LYING)
                return false;
        }
        else
        {
            if(ss.desc != candidate[speaker])
                return false;
        }
    }
    
    return true;
}

bool check_statement_type2(int speaker, int s_idx)  // X is [not] ( divine | human | evil | lying ).
{
    Statement& ss = statement[speaker][s_idx];
    
    if(ss.refer_to == speaker)
        return check_statement_type1(speaker, s_idx);
    
    if(candidate[speaker] == DIVINE || (candidate[speaker] == HUMAN && candidate_envir == DAY)) // tell truth
    {
        if(!ss.neg)
        {
            if(ss.desc != LYING)
            {
                if(candidate[ss.refer_to] != ss.desc)
                    return false;
            }
            else
            {
                if(candidate[ss.refer_to] == DIVINE || (candidate[ss.refer_to] == HUMAN && candidate_envir == DAY))
                    return false;
            }
        }
        else
        {
            if(ss.desc != LYING)
            {
                if(candidate[ss.refer_to] == ss.desc)
                    return false;
            }
            else
            {
                if(candidate[ss.refer_to] == EVIL || (candidate[ss.refer_to] == HUMAN && candidate_envir == NIGHT))
                    return false;
            }
        }
    }
    else    // lie
    {
        if(!ss.neg)
        {
            if(ss.desc != LYING)
            {
                if(candidate[ss.refer_to] == ss.desc)
                    return false;
            }
            else
            {
                if(candidate[ss.refer_to] == EVIL || (candidate[ss.refer_to] == HUMAN && candidate_envir == NIGHT))
                    return false;
            }
        }
        else
        {
            if(ss.desc != LYING)
            {
                if(candidate[ss.refer_to] != ss.desc)
                    return false;
            }
            else
            {
                if(candidate[ss.refer_to] == DIVINE || (candidate[ss.refer_to] == HUMAN && candidate_envir == DAY))
                    return false;
            }
        }
    }
    
    return true;
}

bool check_statement_type3(int speaker, int s_idx)  // It is ( day | night ).
{
    Statement& ss = statement[speaker][s_idx];
    
    if(candidate[speaker] == DIVINE || (candidate[speaker] == HUMAN && candidate_envir == DAY)) // tell truth
    {
        if(ss.desc != candidate_envir)
            return false;
    }
    else    // lie
    {
        if(ss.desc == candidate_envir)
            return false;
    }
    
    return true;
}

bool valid()
{
    int i, j;
    for(i = 0; i < 5; i++)  // check every statement
    {
        for(j = 0; j < statement_num[i]; j++)
        {
            if(statement[i][j].type == SELF)
            {
                if(!check_statement_type1(i, j))
                    return false;
            }
            else if(statement[i][j].type == OTHER)
            {
                if(!check_statement_type2(i, j))
                    return false;
            }
            else
            {
                if(!check_statement_type3(i, j))
                    return false;
            }
        }
    }
    return true;
}

void save_candidate()
{
    int i;
    if(result_envir == UNKNOWN)
        result_envir = candidate_envir;
    else if(result_envir != candidate_envir)
        result_envir = MULTI;
    for(i = 0; i < 5; i++)
    {
        if(result[i] == UNKNOWN)
            result[i] = candidate[i];
        else if(result[i] != candidate[i])
            result[i] = MULTI;
    }
}

void recursive_test(int speaker)
{
    if(speaker == 5)
    {
        if(valid())
            save_candidate();
        return;
    }
    candidate[speaker] = DIVINE;
    recursive_test(speaker+1);
    candidate[speaker] = HUMAN;
    recursive_test(speaker+1);
    candidate[speaker] = EVIL;
    recursive_test(speaker+1);
}

void find_fact()
{
    for(int i = 0; i < 5; i++)
        result[i] = UNKNOWN;
    result_envir = UNKNOWN;
    candidate_envir = DAY;
    recursive_test(0);
    candidate_envir = NIGHT;
    recursive_test(0);
}

bool read_input(int n)
{
    int i;
    char word[10];
    bool ret = true, valid_state;
    memset(statement_num, 0, sizeof(statement_num));
    for(i = 0; i < n; i++)
    {
        scanf("%s", word);
        int speaker = word[0]-'A';
        scanf("%s", word);
        Statement& ss = statement[speaker][statement_num[speaker]];
        valid_state = true;
        if(strcmp(word, "It") == 0)
        {
            ss.type = ENVIR;
            scanf("%*s%s", word);
            if(strcmp(word, "day.") == 0)
                ss.desc = DAY;
            else
                ss.desc = NIGHT;
        }
        else
        {
            if(word[0] == 'I')
                ss.type = SELF;
            else
            {
                ss.type = OTHER;
                ss.refer_to = word[0]-'A';
            }
            scanf("%*s%s", word);
            if(strcmp(word, "not") == 0)
            {
                ss.neg = true;
                scanf("%s", word);
            }
            else
                ss.neg = false;
            if(strcmp(word, "divine.") == 0)
                ss.desc = DIVINE;
            else if(strcmp(word, "human.") == 0)
                ss.desc = HUMAN;
            else if(strcmp(word, "evil.") == 0)
                ss.desc = EVIL;
            else
            {
                ss.desc = LYING;
                if(ss.type == SELF || (ss.type == OTHER && ss.refer_to == speaker))
                {
                    if(!ss.neg)     // I am lying.
                        ret = false;
                    else            // I am not lying.
                        valid_state = false;
                }
            }
        }
        if(valid_state)
            statement_num[speaker]++;
    }
    return ret;
}

int main()
{
    int n, c = 0;
    while(scanf("%d", &n), n)
    {
        printf("Conversation #%d\n", ++c);
        if(read_input(n))
        {
            find_fact();
            bool impossible = true;
            bool deducible = false;
            for(int i = 0; i < 5; i++)
            {
                if(impossible && result[i] != UNKNOWN)
                    impossible = false;
                if(!deducible && result[i] != MULTI)
                    deducible = true;
                if(result[i] != UNKNOWN && result[i] != MULTI)
                    printf("%c is %s.\n", 'A'+i, description_str[result[i]]);
            }
            if(impossible && result_envir != UNKNOWN)
                impossible = false;
            if(!deducible && result_envir != MULTI)
                deducible = true;
            if(result_envir != UNKNOWN && result_envir != MULTI)
                printf("It is %s.\n", description_str[result_envir]);
            if(impossible)
                printf("This is impossible.\n");
            else if(!deducible)
                printf("No facts are deducible.\n");
        }
        else
            printf("This is impossible.\n");
        printf("\n");
    }
    return 0;
}