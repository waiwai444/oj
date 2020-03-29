#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int max_int_ndigit()
{
    int max_int = INT_MAX;
    int ndigits = 0;
    while(max_int > 0)
    {
        max_int /= 10;
        ndigits++;
    }
    return ndigits;
}

int main()
{
    int i, num1_begin, ndigits1, num2_begin, ndigits2, num1, num2;
    double tmp;
    int md = max_int_ndigit();
    char op, input[4096];
    bool overflow;
    while(fgets(input, sizeof(input), stdin))
    {
        int len = strlen(input);
        if(input[len-1] == '\n')
        input[len-1] = '\0';
        i = 0;
        while(input[i] == ' ' || input[i] == '0')
            i++;
        num1_begin = i;
        while(isdigit(input[i]))
            i++;
        ndigits1 = i-num1_begin;
        while(input[i] == ' ')
            i++;
        op = input[i++];
        while(input[i] == ' ' || input[i] == '0')
            i++;
        num2_begin = i;
        while(isdigit(input[i]))
            i++;
        ndigits2 = i-num2_begin;

        printf("%s\n", input);
        overflow = false;
        if(ndigits1 > md || ndigits1 == md && (sscanf(&input[num1_begin], "%lf", &tmp), tmp > (double)INT_MAX))
        {
            printf("first number too big\n");
            overflow = true;
        }
        if(ndigits2 > md || ndigits2 == md && (sscanf(&input[num2_begin], "%lf", &tmp), tmp > (double)INT_MAX))
        {
            printf("second number too big\n");
            overflow = true;
        }
        if(ndigits1 != 0 && ndigits2 != 0)
        {
            if(overflow)
                printf("result too big\n");
            else
            {
                sscanf(&input[num1_begin], "%d", &num1);
                sscanf(&input[num2_begin], "%d", &num2);
                if(op == '+' && INT_MAX-num1 < num2)
                    printf("result too big\n");
                else if(op == '*')
                {
                    if(INT_MAX%num1 == 0)
                    {
                        if(INT_MAX/num1 < num2)
                            printf("result too big\n");
                    }
                    else
                    {
                        if(INT_MAX/num1+1 <= num2)
                            printf("result too big\n");
                    }
                }
            }
        }
    }
    return 0;
}
