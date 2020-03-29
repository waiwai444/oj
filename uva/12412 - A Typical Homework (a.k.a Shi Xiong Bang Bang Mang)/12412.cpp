#include <cstdio>
#include <cstring>
#include <cctype>
#include <list>
#include <algorithm>

#define EPS (1e-5)

struct student_t
{
    char sid[11];
    int cid;
    char name[11];
    int score[4];

    int rank;
    int total;
    double avg;
};

const char *course_name[4] = { "Chinese", "Mathematics", "English", "Programming" };

std::list<student_t> student;
typedef std::list<student_t>::iterator lit;
bool dirty;

inline void print_menu()
{
    printf("Welcome to Student Performance Management System (SPMS).\n"
            "\n"
            "1 - Add\n"
            "2 - Remove\n"
            "3 - Query\n"
            "4 - Show ranking\n"
            "5 - Show Statistics\n"
            "0 - Exit\n"
            "\n");
}

class sid_finder
{
public:
    sid_finder(const char *sid) : sid(sid) {}

    bool operator()(const student_t &s)
    {
        return strcmp(sid, s.sid) == 0;
    };

private:
    const char *sid;

};

class name_finder
{
public:
    name_finder(const char *name) : name(name) {}

    bool operator()(const student_t &s)
    {
        return strcmp(name, s.name) == 0;
    }

private:
    const char *name;

};

void add()
{
    student_t s;
    lit it;
    for(;;)
    {
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s", s.sid);
        if(s.sid[0] == '0' && s.sid[1] == '\0')
            break;
        scanf("%d%s%d%d%d%d", &s.cid, s.name, &s.score[0], &s.score[1], &s.score[2], &s.score[3]);
        it = std::find_if(student.begin(), student.end(), sid_finder(s.sid));
        if(it != student.end())
            printf("Duplicated SID.\n");
        else
        {
            student.push_back(s);
            dirty = true;
        }
    }
}

void remove()
{
    char key[12];
    int cnt = 0;
    lit it;
    for(;;)
    {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s", key);
        if(isdigit(key[0]))
        {
            if(key[1] == '\0')
                break;
            it = std::find_if(student.begin(), student.end(), sid_finder(key));
            if(it != student.end())
            {
                student.erase(it);
                cnt = 1;
            }
            else
                cnt = 0;
        }
        else
        {
            cnt = student.size();
            student.remove_if(name_finder(key));
            cnt -= student.size();
        }
        if(cnt > 0)
            dirty = true;
        printf("%d student(s) removed.\n", cnt);
    }
}

lit idx[100];

bool cmp_idx(const lit &it1, const lit &it2)
{
    return it1->total > it2->total;
}

void query()
{
    int i;
    char key[12];
    lit it;

    if(dirty)
    {
        for(i = 0, it = student.begin(); it != student.end(); ++i, ++it)
        {
            idx[i] = it;
            it->total = it->score[0]+it->score[1]+it->score[2]+it->score[3];
            it->avg = it->total/4.0L;
        }
        std::sort(&idx[0], &idx[student.size()], cmp_idx);
        idx[0]->rank = 1;
        for(i = 1; i < student.size(); i++)
        {
            if(idx[i]->total == idx[i-1]->total)
                idx[i]->rank = idx[i-1]->rank;
            else
                idx[i]->rank = i+1;
        }
        dirty = false;
    }

    for(;;)
    {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s", key);
        if(isdigit(key[0]))
        {
            if(key[1] == '\0')
                break;
            it = std::find_if(student.begin(), student.end(), sid_finder(key));
            if(it != student.end())
                printf("%d %s %d %s %d %d %d %d %d %.2f\n", it->rank, it->sid, it->cid, it->name,
                        it->score[0], it->score[1], it->score[2], it->score[3], it->total, it->avg+EPS);
        }
        else
        {
            for(it = student.begin(); it != student.end(); ++it)
                if(strcmp(it->name, key) == 0)
                    printf("%d %s %d %s %d %d %d %d %d %.2f\n", it->rank, it->sid, it->cid, it->name,
                            it->score[0], it->score[1], it->score[2], it->score[3], it->total, it->avg+EPS);
        }
    }
}

inline void show_ranking()
{
    printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}

void show_statistics()
{
    lit it;
    int i, cid, pc;
    int pass[4], fail[4], pass_all, pass3, pass2, pass1, fail_all;
    double avg[4];

    for(i = 0; i < 4; i++)
        pass[i] = fail[i] = 0, avg[i] = 0;
    pass_all = pass3 = pass2 = pass1 = fail_all = 0;

    printf("Please enter class ID, 0 for the whole statistics.\n");
    scanf("%d", &cid);

    for(it = student.begin(); it != student.end(); ++it)
    {
        if(cid != 0 && it->cid != cid)
            continue;
        pc = 0;
        for(i = 0; i < 4; i++)
        {
            if(it->score[i] >= 60)
            {
                ++pass[i];
                ++pc;
            }
            else
                ++fail[i];
            avg[i] += it->score[i];
        }
        if(pc == 0)
            ++fail_all;
        else
        {
            if(pc >= 1)
                ++pass1;
            if(pc >= 2)
                ++pass2;
            if(pc >= 3)
                ++pass3;
            if(pc == 4)
                ++pass_all;
        }
    }

    for(i = 0; i < 4; i++)
        printf("%s\n"
                "Average Score: %.2f\n"
                "Number of passed students: %d\n"
                "Number of failed students: %d\n"
                "\n",
                course_name[i], avg[i]/(pass[i]+fail[i])+EPS, pass[i], fail[i]);
    printf("Overall:\n"
            "Number of students who passed all subjects: %d\n"
            "Number of students who passed 3 or more subjects: %d\n"
            "Number of students who passed 2 or more subjects: %d\n"
            "Number of students who passed 1 or more subjects: %d\n"
            "Number of students who failed all subjects: %d\n"
            "\n",
            pass_all, pass3, pass2, pass1, fail_all);
}

int main()
{
    int command;
    for(;;)
    {
        print_menu();
        scanf("%d", &command);
        if(command == 1)
            add();
        else if(command == 2)
            remove();
        else if(command == 3)
            query();
        else if(command == 4)
            show_ranking();
        else if(command == 5)
            show_statistics();
        else if(command == 0)
            break;
    }
    return 0;
}

