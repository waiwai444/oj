#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#define ONSHELF 0
#define BORROWED 1
#define ONDESK 2

struct book_t
{
    char name[81];
    char author[81];
    int status;
};

std::vector<book_t> books;
std::map<std::string, int> book_idx;

bool cmp_books(const book_t &b1, const book_t &b2)
{
    int r = strcmp(b1.author, b2.author);
    if(r != 0)
        return r < 0;
    return strcmp(b1.name, b2.name) < 0;
}

int main()
{
    int i, j, s;
    char line[200], *cmd, *name;
    book_t bk;
    bk.status = ONSHELF;
    while(fgets(line, sizeof(line), stdin))
    {
        if(line[0] == 'E')
            break;
        strcpy(bk.name, strtok(line, "\""));
        strtok(NULL, " ");
        strcpy(bk.author, strtok(NULL, "\n\r"));
        books.push_back(bk);
    }
    std::sort(books.begin(), books.end(), cmp_books);
    for(i = 0; i < books.size(); i++)
        book_idx[books[i].name] = i;
    while(fgets(line, sizeof(line), stdin))
    {
        if(line[0] == 'E')
            break;
        cmd = strtok(line, " \n\r");
        name = strtok(NULL, "\"");
        if(*cmd == 'B')
            books[book_idx[name]].status = BORROWED;
        else if(*cmd == 'R')
            books[book_idx[name]].status = ONDESK;
        else
        {
            j = -1;
            for(i = 0; i < books.size(); ++i)
            {
                s = books[i].status;
                if(s == ONSHELF)
                    j = i;
                else if(s == ONDESK)
                {
                    if(j < 0)
                        printf("Put \"%s\" first\n", books[i].name);
                    else
                        printf("Put \"%s\" after \"%s\"\n", books[i].name, books[j].name);
                    books[i].status = ONSHELF;
                    j = i;
                }
            }
            puts("END");
        }
    }
    return 0;
}

