#include <stdio.h>

#define ADD 0
#define DIV 1
#define DUP 2
#define MUL 3
#define SUB 4

#define LIMIT 30000
#define MAX_N 10
#define MAX_COM 10
#define MAX_STACK_SIZE 6

int n;
int x[MAX_N], y[MAX_N];

struct command_seq
{
    char com_num;
    char command[MAX_COM];
};

struct stack
{
    char top;
    int value[MAX_N][MAX_STACK_SIZE];
};

struct status
{
    command_seq cs;
    stack st;
};

struct queue
{
    int _front, _back;
    status *_elem;
    queue() { _front = _back = 0; _elem = new status[18000]; }  // 18000 suffices for 10 commands
    ~queue() { delete[] _elem; }
    void init() { _front = _back = 0; }
    bool empty() { return _front == _back; }
    void push(const status &s) { _elem[_back++] = s; }
    void pop() { _front++; }
    status front() { return _elem[_front]; }
    status &peek_front() { return _elem[_front]; }
};

inline bool is_finished(const stack &sv)
{
    if(sv.top != 0)
        return false;
    for(int i = 0; i < n; i++)
        if(sv.value[i][0] != y[i])
            return false;
    return true;
}

bool add(command_seq *cs, stack *sv)
{
    int i, a, b;
    for(i = 0; i < n; i++)
    {
        if(sv->top < 1)
            return false;
        a = sv->value[i][sv->top];
        b = sv->value[i][sv->top-1];
        if(b+a <= LIMIT && b+a >= -LIMIT)
            sv->value[i][sv->top-1] = b+a;
        else
            return false;
    }
    sv->top--;
    cs->command[cs->com_num++] = ADD;
    return true;
}

bool sub(command_seq *cs, stack *sv)
{
    int i, a, b;
    for(i = 0; i < n; i++)
    {
        if(sv->top < 1)
            return false;
        a = sv->value[i][sv->top];
        b = sv->value[i][sv->top-1];
        if(b-a <= LIMIT && b-a >= -LIMIT)
            sv->value[i][sv->top-1] = b-a;
        else
            return false;
    }
    sv->top--;
    cs->command[cs->com_num++] = SUB;
    return true;
}

bool mul(command_seq *cs, stack *sv)
{
    int i, a, b;
    for(i = 0; i < n; i++)
    {
        if(sv->top < 1)
            return false;
        a = sv->value[i][sv->top];
        b = sv->value[i][sv->top-1];
        if(b*a <= LIMIT && b*a >= -LIMIT)
            sv->value[i][sv->top-1] = b*a;
        else
            return false;
    }
    sv->top--;
    cs->command[cs->com_num++] = MUL;
    return true;
}

bool div(command_seq *cs, stack *sv)
{
    int i, a, b;
    for(i = 0; i < n; i++)
    {
        if(sv->top < 1)
            return false;
        a = sv->value[i][sv->top];
        if(a == 0)
            return false;
        b = sv->value[i][sv->top-1];
        if(b/a <= LIMIT && b/a >= -LIMIT)
            sv->value[i][sv->top-1] = b/a;
        else
            return false;
    }
    sv->top--;
    cs->command[cs->com_num++] = DIV;
    return true;
}

bool dup(command_seq *cs, stack *sv)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(sv->top < 0 || sv->top > MAX_COM-cs->com_num)
            return false;
        sv->value[i][sv->top+1] = sv->value[i][sv->top];
    }
    sv->top++;
    cs->command[cs->com_num++] = DUP;
    return true;
}

bool (*op_set[5])(command_seq *, stack *) = { add, div, dup, mul, sub };
queue sq;

bool bfs(command_seq *result_com)
{
    int i;
    sq.init();
    status ss, ss2;
    ss.cs.com_num = 0;
    for(i = 0; i < n; i++)
    {
        ss.st.top = 0;
        ss.st.value[i][0] = x[i];
    }
    if(is_finished(ss.st))
    {
        *result_com = ss.cs;
        return true;
    }
    sq.push(ss);
    
    while(!sq.empty())
    {
        ss = sq.peek_front();
        sq.pop();
        for(i = 0; i < 5; i++)
        {
            ss2 = ss;
            if((*op_set[i])(&ss2.cs, &ss2.st))
            {
                if(is_finished(ss2.st))
                {
                    *result_com = ss2.cs;
                    return true;
                }
                if(ss2.cs.com_num < MAX_COM)
                    sq.push(ss2);
            }
        }
    }
    
    return false;
}

void output(const command_seq &cs)
{
    int i;
    for(i = 0; i < cs.com_num; i++)
    {
        if(i > 0)
            printf(" ");
        switch(cs.command[i])
        {
            case ADD:
                printf("ADD");
                break;
            case SUB:
                printf("SUB");
                break;
            case MUL:
                printf("MUL");
                break;
            case DIV:
                printf("DIV");
                break;
            case DUP:
                printf("DUP");
                break;
        }
    }
    printf("\n\n");
}

int main()
{
    int i, tc = 0;
    command_seq cs;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
            scanf("%d", &x[i]);
        for(i = 0; i < n; i++)
            scanf("%d", &y[i]);
        printf("Program %d\n", ++tc);
        if(bfs(&cs))
        {
            if(cs.com_num == 0)
                printf("Empty sequence\n\n");
            else
                output(cs);
        }
        else
            printf("Impossible\n\n");
    }
    return 0;
}
