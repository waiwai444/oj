#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

char input[21];
int input_len;

int compare(char a, char b)
{
    if(tolower(a) == tolower(b))
        return a < b;
    return tolower(a) < tolower(b);
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%s", input);
        input_len = (int)strlen(input);
        std::sort(input, &input[input_len], compare);
        do
        {
            printf("%s\n", input);
        } while(std::next_permutation(input, &input[input_len], compare));
    }
    return 0;
}