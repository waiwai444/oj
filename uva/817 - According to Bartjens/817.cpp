#include <cstdio>

char input[12];
char ans[20];
int n_ans;

int calc(char op, int a, int b)
{
    switch(op)
    {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    }
    return 0;
}

void dfs(int input_pos, int ans_pos, int bot, char bot_op, int top, char top_op)
{
    if(input[input_pos] == '=')
    {
        ans[ans_pos] = '=';
        ans[ans_pos+1] = '\0';
        if(input_pos != ans_pos && bot == 2000)
        {
            ++n_ans;
            std::printf("  %s\n", ans);
        }
        return;
    }
    int n = 0, m;
    for(int i = input_pos, j = ans_pos; input[i] != '='; ++i, ++j)
    {
        m = n = n*10+input[i]-'0';
        ans[j] = input[i];
        if(top_op)
            m = n*top;
        if(input[i+1] == '=')
            dfs(i+1, j+1, calc(bot_op, bot, m), 0, 0, 0);
        else
        {
            ans[j+1] = '+';
            dfs(i+1, j+2, calc(bot_op, bot, m), '+', 0, 0);
            ans[j+1] = '-';
            dfs(i+1, j+2, calc(bot_op, bot, m), '-', 0, 0);
            ans[j+1] = '*';
            dfs(i+1, j+2, bot, bot_op, m, '*');
        }
        if(input[input_pos] == '0')
            break;
    }
}

int main()
{
    int tc = 0;
    while(std::scanf("%s", input))
    {
        if(input[0] == '=')
            break;
        n_ans = 0;
        std::printf("Problem %d\n", ++tc);
        dfs(0, 0, 0, '+', 0, 0);
        if(n_ans == 0)
            std::puts("  IMPOSSIBLE");
    }
    return 0;
}
