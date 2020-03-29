#include <stdio.h>
#include <string.h>

#define MAXN 1000

char fact[MAXN+1][3000];
int ndigit[MAXN+1];
char output[3000];

int main()
{
    int i, x, n, carry, temp;
    
    memset(ndigit, 0, sizeof(ndigit));
    fact[0][0] = fact[MAXN][0] = 1;
    ndigit[0] = ndigit[MAXN] = 1;
    for(x = 1; x <= MAXN; x++)
    {
        carry = 0;
        for(i = 0; i < ndigit[MAXN]; i++)
        {
            temp = fact[MAXN][i]*x+carry;
            fact[MAXN][i] = temp%10;
            carry = temp/10;
        }
        while(carry > 0)
        {
            fact[MAXN][ndigit[MAXN]++] = carry%10;
            carry /= 10;
        }

        if(x < MAXN)
        {
                memcpy(fact[x], fact[MAXN], ndigit[MAXN]);
                ndigit[x] = ndigit[MAXN];
        }
    }
    
    while(scanf("%d", &n) != EOF)
    {        
        for(i = 0; i < ndigit[n]; i++)
            output[i] = fact[n][ndigit[n]-i-1]+'0';
        output[ndigit[n]] = '\0';
        printf("%d!\n%s\n", n, output);
    }
    return 0;
}
