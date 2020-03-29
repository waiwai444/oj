#include <cstdio>
#include <cstring>

int np;
int ta, tp, tl, tu, te, qt;

enum cmd_type_e { ASSIGN, PRINT, LOCK, UNLOCK, END };

struct cmd_t
{
    cmd_type_e type;
    char var;
    int num;
};

struct prog_t
{
    int id;
    cmd_t cmds[25];
    int pc;
    int qt;
    prog_t *next;
} progs[10];

struct queue_t
{
    prog_t *head, *tail;
} ready, blocked;

int vars[26];
bool locked;

inline void set_var(char var, int num)
{
    vars[var-'a'] = num;
}

inline int get_var(char var)
{
    return vars[var-'a'];
}

inline void push_front(queue_t *q, prog_t *p)
{
    if(!q->tail)
        q->tail = p;
    p->next = q->head;
    q->head = p;
}

inline void push_back(queue_t *q, prog_t *p)
{
    if(!q->tail)
        q->head = q->tail = p;
    else
        q->tail->next = p, q->tail = p;
    p->next = NULL;
}

inline prog_t *pop_front(queue_t *q)
{
    prog_t *p = q->head;
    q->head = p->next;
    p->next = NULL;
    if(!q->head)
        q->tail = NULL;
    return p;
}

inline bool is_empty(const queue_t *q)
{
    return !q->head;
}

void exec()
{
    int i;
    bool r;
    prog_t *p;
    std::memset(vars, 0, sizeof(vars));
    locked = false;
    for(i = 0; i < np; ++i)
    {
        progs[i].pc = 0;
        push_back(&ready, &progs[i]);
    }
    for(;;)
    {
        if(is_empty(&ready) && is_empty(&blocked))
            break;
        p = pop_front(&ready);
        p->qt = qt;
        r = true;
        while(p->qt > 0)
        {
            cmd_t *c = &p->cmds[p->pc];
            switch(c->type)
            {
            case ASSIGN:
                set_var(c->var, c->num);
                p->qt -= ta;
                ++p->pc;
                break;
            case PRINT:
                std::printf("%d: %d\n", p->id+1, get_var(c->var));
                p->qt -= tp;
                ++p->pc;
                break;
            case LOCK:
                if(locked)
                {
                    p->qt = 0;
                    r = false;
                    push_back(&blocked, p);
                }
                else
                {
                    locked = true;
                    p->qt -= tl;
                    ++p->pc;
                }
                break;
            case UNLOCK:
                locked = false;
                if(!is_empty(&blocked))
                {
                    prog_t *b = pop_front(&blocked);
                    push_front(&ready, b);
                }
                p->qt -= tu;
                ++p->pc;
                break;
            default: // END
                p->qt = 0;
                r = false;
                break;
            }
        }
        if(r)
            push_back(&ready, p);
    }
}

int main()
{
    int tc, i, j, num;
    char line[16], var[2];
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d%d%d%d%d%d%d", &np, &ta, &tp, &tl, &tu, &te, &qt);
        std::fgets(line, sizeof(line), stdin);
        for(i = 0; i < np; ++i)
        {
            progs[i].id = i;
            j = 0;
            for(;;)
            {
                std::fgets(line, sizeof(line), stdin);
                if(line[0] == 'p' && line[1] == 'r')
                {
                    std::sscanf(line, "%*s %s", var);
                    progs[i].cmds[j].type = PRINT;
                    progs[i].cmds[j].var = var[0];
                }
                else if(line[0] == 'l' && line[1] == 'o')
                    progs[i].cmds[j].type = LOCK;
                else if(line[0] == 'u' && line[1] == 'n')
                    progs[i].cmds[j].type = UNLOCK;
                else if(line[0] == 'e' && line[1] == 'n')
                {
                    progs[i].cmds[j].type = END;
                    break;
                }
                else
                {
                    std::sscanf(line, "%s = %d", var, &num);
                    progs[i].cmds[j].type = ASSIGN;
                    progs[i].cmds[j].var = var[0];
                    progs[i].cmds[j].num = num;
                }
                ++j;
            }
        }
        exec();
        if(tc)
            std::putchar('\n');
    }
    return 0;
}

