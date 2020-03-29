#include <stdio.h>
#include <string.h>
#include <algorithm>

char input[11];
int input_len;

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%s", input);
        input_len = (int)strlen(input);
        std::sort(input, &input[input_len]);
        do
        {
            printf("%s\n", input);
        } while(std::next_permutation(input, &input[input_len]));
        printf("\n");
    }
    return 0;
}