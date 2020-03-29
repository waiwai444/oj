#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compar(const void *p1, const void *p2)
{
    return strcmp((const char *)p1, (const char *)p2);
}

int main()
{
    int i, j, dict_size = 0;
    char dict[101][7], scrambled[7];
    int alpha_counter[100][26], s_counter[26];
    bool found;
    memset(alpha_counter, 0, sizeof(alpha_counter));
    while(scanf("%s", dict[dict_size]), dict[dict_size][0] != 'X')
        dict_size++;
    qsort(dict, dict_size, 7*sizeof(char), compar);
    for(i = 0; i < dict_size; i++)
        for(j = 0; dict[i][j] != '\0'; j++)
            alpha_counter[i][dict[i][j]-'a']++;
    while(scanf("%s", scrambled), scrambled[0] != 'X')
    {
        memset(s_counter, 0, sizeof(s_counter));
        for(i = 0; scrambled[i] != '\0'; i++)
            s_counter[scrambled[i]-'a']++;
        found = false;
        for(i = 0; i < dict_size; i++)
        {
            for(j = 0; j < 26; j++)
                if(alpha_counter[i][j] != s_counter[j])
                    break;
            if(j == 26)
            {
                printf("%s\n", dict[i]);
                if(!found)
                    found = true;
            }
        }
        if(!found)
            printf("NOT A VALID WORD\n******\n");
        else
            printf("******\n");
    }
    return 0;
}
