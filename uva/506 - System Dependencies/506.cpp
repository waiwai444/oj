#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

#define NOT_INST 0
#define EXP_INST 1
#define IMP_INST 2

struct item_t
{
    char name[16];
    std::vector<int> dep;
    std::vector<int> usr;
    char inst;
};

std::vector<item_t> items;
std::map<std::string, int> idx;
std::list<int> inst_list;

void remove_newline(char *str)
{
    char *p = str;
    while(*p) ++p;
    --p;
    while(p >= str && (*p == '\r' || *p == '\n'))
        *p-- = '\0';
}

int add_new_item(char *item)
{
    item_t itm;
    int id = items.size();
    items.push_back(itm);
    std::strcpy(items[id].name, item);
    items[id].inst = NOT_INST;
    idx[item] = id;
    return id;
}

void recursive_install(int id, char met)
{
    int i, idd;
    for(i = 0; i < items[id].dep.size(); ++i)
        if(items[idd = items[id].dep[i]].inst == NOT_INST)
            recursive_install(idd, IMP_INST);
    std::printf("   Installing %s\n", items[id].name);
    items[id].inst = met;
    inst_list.push_back(id);
}

void install(char *item)
{
    int id;
    std::map<std::string, int>::iterator it = idx.find(item);
    if(it == idx.end())
        id = add_new_item(item);
    else
        id = it->second;
    if(items[id].inst == NOT_INST)
        recursive_install(id, EXP_INST);
    else
        std::printf("   %s is already installed.\n", item);
}

bool recursive_remove(int id)
{
    int i, id2;
    for(i = 0; i < items[id].usr.size(); ++i)
        if(items[id2 = items[id].usr[i]].inst != NOT_INST)
            return false;
    std::printf("   Removing %s\n", items[id].name);
    items[id].inst = NOT_INST;
    inst_list.erase(std::find(inst_list.begin(), inst_list.end(), id));
    for(i = 0; i < items[id].dep.size(); ++i)
        if(items[id2 = items[id].dep[i]].inst == IMP_INST)
            recursive_remove(id2);
    return true;
}

void remove(char *item)
{
    int id;
    std::map<std::string, int>::iterator it = idx.find(item);
    if(it == idx.end())
        id = add_new_item(item);
    else
        id = it->second;
    if(items[id].inst != NOT_INST)
    {
        if(!recursive_remove(id))
            std::printf("   %s is still needed.\n", item);
    }
    else
        std::printf("   %s is not installed.\n", item);
}

void list()
{
    std::list<int>::const_iterator it;
    for(it = inst_list.begin(); it != inst_list.end(); ++it)
        std::printf("   %s\n", items[*it].name);
}

void process_cmd(char *cmd)
{
    char *ptr, *item;
    int id1, idd;
    std::map<std::string, int>::iterator it;
    std::puts(cmd);
    ptr = std::strtok(cmd, " ");
    if(!ptr)
        return;
    if(*ptr == 'D')
    {
        item = std::strtok(NULL, " ");
        if((it = idx.find(item)) == idx.end())
            id1 = add_new_item(item);
        else
            id1 = it->second;
        while(item = std::strtok(NULL, " "))
        {
            if((it = idx.find(item)) == idx.end())
                idd = add_new_item(item);
            else
                idd = it->second;
            items[idd].usr.push_back(id1);
            items[id1].dep.push_back(idd);
        }
    }
    else if(*ptr == 'I')
        install(std::strtok(NULL, " "));
    else if(*ptr == 'R')
        remove(std::strtok(NULL, " "));
    else if(*ptr == 'L')
        list();
}

int main()
{
    char line[100];
    items.reserve(1000);
    while(std::fgets(line, sizeof(line), stdin))
    {
        items.clear();
        idx.clear();
        inst_list.clear();
        while(line[0] != 'E')
        {
            remove_newline(line);
            process_cmd(line);
            std::fgets(line, sizeof(line), stdin);
        }
        std::puts("END");
    }
    return 0;
}

