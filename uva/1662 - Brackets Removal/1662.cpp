#include <cstdio>
#include <cstring>

#define SIZE 1000

char input[SIZE+5], output[SIZE+2];
int len;
int lbra[SIZE], top;

bool has_top_add_sub(int l, int r)
{
    int b = 0, i;
    for(i = l; i <= r; i++)
    {
        if(input[i] == '(')
            ++b;
        else if(input[i] == ')')
            --b;
        else if(input[i] == '+' || input[i] == '-')
        {
            if(b == 0)
                break;
        }
    }
    return i <= r;
}

bool removable(int pos)
{
    int l = lbra[top-1];
    char lop = input[l-1], rop = input[pos+1];
    if((lop == '*' || lop == '/') || (rop == '*' || rop == '/'))
        return !has_top_add_sub(l+1, pos-1);
    return true;
}

void rev_add_sub(int l, int r)
{
    int b = 0, i;
    for(i = l; i <= r; i++)
    {
        if(input[i] == '(')
            ++b;
        if(input[i] == ')')
            --b;
        else if(input[i] == '+' && b == 0)
            input[i] = '-';
        else if(input[i] == '-' && b == 0)
            input[i] = '+';
    }
}

void rev_mul_div(int l, int r)
{
    int b = 0, i;
    for(i = l; i <= r; i++)
    {
        if(input[i] == '(')
            ++b;
        if(input[i] == ')')
            --b;
        else if(input[i] == '*' && b == 0)
            input[i] = '/';
        else if(input[i] == '/' && b == 0)
            input[i] = '*';
    }
}

void solve()
{
    int i, j;
    len = strlen(input+1);
    top = 0;
    for(i = 1; i <= len; i++)
    {
        if(input[i] == '(')
            lbra[top++] = i;
        else if(input[i] == ')')
        {
            if(removable(i))
            {
                input[lbra[top-1]] = input[i] = 0;
                if(input[lbra[top-1]-1] == '-')
                    rev_add_sub(lbra[top-1]+1, i-1);
                else if(input[lbra[top-1]-1] == '/')
                    rev_mul_div(lbra[top-1]+1, i-1);
            }
            --top;
        }
    }
    for(i = 1, j = 0; i <= len; i++)
        if(input[i])
            output[j++] = input[i];
    output[j] = 0;
}

int main()
{
    while(fgets(input+1, sizeof(input)-1, stdin))
    {
        len = strlen(input+1);
        while(input[len] == '\n' || input[len] == '\r')
            input[len--] = 0;
        solve();
        printf("%s\n", output);
    }
    return 0;
}

