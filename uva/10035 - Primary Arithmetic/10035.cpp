#include <cstdio>
#include <memory.h>

#define MAX_DIGIT 10

struct NaturalNumber {
    char digit[MAX_DIGIT];
    int lastdigit;
};

int main()
{
    int i, l, s;
    char c;
    int carry;
    NaturalNumber x, y;
    while(true)
    {
        memset(&x, 0, sizeof(x));
        memset(&y, 0, sizeof(y));
        x.lastdigit = y.lastdigit = -1;
        i = 0;
        while(scanf("%c", &c))
        {
            if(c==' ')
                break;
            x.digit[i++] = c-'0';
        }
        x.lastdigit = i-1;
        i = 0;
        while(scanf("%c", &c))
        {
            if(c=='\n')
                break;
            y.digit[i++] = c-'0';
        }
        y.lastdigit = i-1;
        if(x.lastdigit==0 && x.digit[0]==0 && y.lastdigit==0 && y.digit[0]==0)
            break;
        l = x.lastdigit<y.lastdigit?x.lastdigit:y.lastdigit;
        carry = s = 0;
        for(i=0; i<=l; i++)
        {
            if(x.digit[x.lastdigit-i]+y.digit[y.lastdigit-i]+carry>9)
            {
                carry = 1;
                s++;
            }
            else
                carry = 0;
        }
        if(carry==1)
        {
            if(x.lastdigit>y.lastdigit)
            {
                for(; i<=x.lastdigit; i++)
                {
                    if(x.digit[x.lastdigit-i]<9)
                        break;
                    s++;
                }
            }
            else if(x.lastdigit<y.lastdigit)
            {
                for(; i<=y.lastdigit; i++)
                {
                    if(y.digit[y.lastdigit-i]<9)
                        break;
                    s++;
                }
            }
        }
        if(s==0)
            printf("No carry operation.\n");
        else if(s==1)
            printf("1 carry operation.\n");
        else
            printf("%d carry operations.\n", s);
    }
    return 0;
}
