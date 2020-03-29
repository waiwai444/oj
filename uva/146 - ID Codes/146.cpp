#include <stdio.h>
#include <string.h>

char code[51], next[51];
int code_len;
int count[26];

bool recur(int pos, bool &code_found)
{
    int i;
    for(i = code_found ? 'a' : code[pos]; i <= 'z'; i++)
    {
        if(count[i-'a'] == 0)
            continue;
        next[pos] = i;
        count[i-'a']--;
        if(pos < code_len-1)
        {
            if(recur(pos+1, code_found))
                return true;
        }
        else
        {
            if(!code_found)
            {
                code_found = true;
                count[i-'a']++;
                return false;
            }
            return true;
        }
        count[i-'a']++;
    }
    return false;
}

bool next_permutation()
{
    memset(count, 0, sizeof(count));
    code_len = (int)strlen(code);
    for(int i = 0; i < code_len; i++)
        count[code[i]-'a']++;
    bool code_found = false;
    return recur(0, code_found);
}

int main()
{
    while(scanf("%s", code), code[0] != '#')
    {
        if(next_permutation())
        {
            next[code_len] = '\0';
            printf("%s\n", next);
        }
        else
            printf("No Successor\n");
    }
    return 0;
}