#include <cstring>
#include <cctype>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#define SGL 0
#define AND 1
#define OR 2
#define NOT 3

struct bucket_t
{
    std::map<int, std::vector<int> > entries;
};

struct trie_node_t
{
    bucket_t *bkt;
    trie_node_t *child[26];
    trie_node_t() : bkt(0) { memset(child, 0, sizeof(child)); }
};

struct query_t
{
    char type;
    std::string term[2];
};

int n, m;
std::vector<std::vector<std::string> > docs;
std::vector<query_t> queries;
trie_node_t key_tree;

void insert_key(const std::string &key)
{
    int i, j;
    trie_node_t *pt = &key_tree;
    for(i = 0; i < key.length(); ++i)
    {
        j = tolower(key[i])-'a';
        if(!pt->child[j])
            pt->child[j] = new trie_node_t;
        pt = pt->child[j];
    }
    if(!pt->bkt)
        pt->bkt = new bucket_t;
}

bucket_t *find_key(const std::string &key)
{
    int i, j;
    trie_node_t *pt = &key_tree;
    for(i = 0; i < key.length(); ++i)
    {
        j = tolower(key[i])-'a';
        if(!pt->child[j])
            return NULL;
        pt = pt->child[j];
    }
    return pt->bkt;
}

void parse_query(const std::string &str)
{
    query_t q;
    std::istringstream iss(str);
    iss >> q.term[0];
    if(q.term[0] == "NOT")
    {
        q.type = NOT;
        iss >> q.term[0];
    }
    else if(iss.eof())
        q.type = SGL;
    else
    {
        iss >> q.term[1];
        if(q.term[1] == "AND")
            q.type = AND;
        else
            q.type = OR;
        iss >> q.term[1];
        insert_key(q.term[1]);
    }
    insert_key(q.term[0]);
    queries.push_back(q);
}

void parse_documents()
{
    int i, j, k, l;
    bucket_t *bkt;
    for(i = 0; i < n; ++i)
    {
        std::vector<std::string> &doc = docs[i];
        for(j = 0; j < doc.size(); ++j)
        {
            std::string &line = doc[j];
            for(k = 0; k < line.length(); ++k)
            {
                if(!isalpha(line[k]))
                    continue;
                for(l = k; l < line.length(); ++l)
                    if(!isalpha(line[l]))
                        break;
                bkt = find_key(line.substr(k, l-k));
                if(bkt && (bkt->entries[i].size() == 0 || bkt->entries[i].back() != j))
                    bkt->entries[i].push_back(j);
                k = l;
            }
        }
    }
}

bool handle_single_term_query(const std::string &term)
{
    int i, d, l;
    std::map<int, std::vector<int> >::const_iterator it;
    bucket_t *bkt = find_key(term);
    if(bkt->entries.size() == 0)
        return false;
    for(it = bkt->entries.begin(); it != bkt->entries.end(); ++it)
    {
        if(it != bkt->entries.begin())
            std::cout << "----------\n";
        d = it->first;
        for(i = 0; i < it->second.size(); ++i)
        {
            l = it->second[i];
            std::cout << docs[d][l] << '\n';
        }
    }
    return true;
}

bool handle_and_query(const std::string &term1, const std::string &term2)
{
    int i, j, d;
    bool first = true;
    std::map<int, std::vector<int> >::const_iterator it1, it2;
    bucket_t *bkt1 = find_key(term1), *bkt2 = find_key(term2);
    for(it1 = bkt1->entries.begin(); it1 != bkt1->entries.end(); ++it1)
    {
        d = it1->first;
        it2 = bkt2->entries.find(d);
        if(it2 == bkt2->entries.end())
            continue;
        !first ? (std::cout << "----------\n", false) : first = false;
        const std::vector<int> &lines1 = it1->second, &lines2 = it2->second;
        i = j = 0;
        while(i < lines1.size() && j < lines2.size())
        {
            if(lines1[i] < lines2[j])
                std::cout << docs[d][lines1[i++]] << '\n';
            else if(lines1[i] > lines2[j])
                std::cout << docs[d][lines2[j++]] << '\n';
            else
            {
                std::cout << docs[d][lines1[i++]] << '\n';
                ++j;
            }
        }
        while(i < lines1.size())
            std::cout << docs[d][lines1[i++]] << '\n';
        while(j < lines2.size())
            std::cout << docs[d][lines2[j++]] << '\n';
    }
    return !first;
}

bool handle_or_query(const std::string &term1, const std::string &term2)
{
    int i, j, d;
    bool first = true;
    std::map<int, std::vector<int> >::const_iterator it1, it2;
    bucket_t *bkt1 = find_key(term1), *bkt2 = find_key(term2);
    it1 = bkt1->entries.begin(), it2 = bkt2->entries.begin();
    while(it1 != bkt1->entries.end() && it2 != bkt2->entries.end())
    {
        !first ? (std::cout << "----------\n", false) : first = false;
        if(it1->first < it2->first)
        {
            d = it1->first;
            const std::vector<int> &lines = it1->second;
            for(i = 0; i < lines.size(); ++i)
                std::cout << docs[d][lines[i]] << '\n';
            ++it1;
        }
        else if(it1->first > it2->first)
        {
            d = it2->first;
            const std::vector<int> &lines = it2->second;
            for(i = 0; i < lines.size(); ++i)
                std::cout << docs[d][lines[i]] << '\n';
            ++it2;
        }
        else
        {
            d = it1->first;
            const std::vector<int> &lines1 = it1->second, &lines2 = it2->second;
            i = j = 0;
            while(i < lines1.size() && j < lines2.size())
            {
                if(lines1[i] < lines2[j])
                    std::cout << docs[d][lines1[i++]] << '\n';
                else if(lines1[i] > lines2[j])
                    std::cout << docs[d][lines2[j++]] << '\n';
                else
                {
                    std::cout << docs[d][lines1[i++]] << '\n';
                    ++j;
                }
            }
            while(i < lines1.size())
                std::cout << docs[d][lines1[i++]] << '\n';
            while(j < lines2.size())
                std::cout << docs[d][lines2[j++]] << '\n';
            ++it1, ++it2;
        }
    }
    while(it1 != bkt1->entries.end())
    {
        !first ? (std::cout << "----------\n", false) : first = false;
        d = it1->first;
        const std::vector<int> &lines = it1->second;
        for(i = 0; i < lines.size(); ++i)
            std::cout << docs[d][lines[i]] << '\n';
        ++it1;
    }
    while(it2 != bkt2->entries.end())
    {
        !first ? (std::cout << "----------\n", false) : first = false;
        d = it2->first;
        const std::vector<int> &lines = it2->second;
        for(i = 0; i < lines.size(); ++i)
            std::cout << docs[d][lines[i]] << '\n';
        ++it2;
    }
    return !first;
}

bool handle_not_query(const std::string &term)
{
    int i, j, k;
    bool first = true;
    bucket_t *bkt = find_key(term);
    std::map<int, std::vector<int> >::const_iterator it;
    i = 0;
    for(it = bkt->entries.begin(); it != bkt->entries.end(); ++it)
    {
        j = it->first;
        for(; i < j; ++i)
        {
            !first ? (std::cout << "----------\n", false) : first = false;
            for(k = 0; k < docs[i].size(); ++k)
                std::cout << docs[i][k] << '\n';
        }
        i = j+1;
    }
    for(; i < n; ++i)
    {
        !first ? (std::cout << "----------\n", false) : first = false;
        for(k = 0; k < docs[i].size(); ++k)
            std::cout << docs[i][k] << '\n';
    }
    return !first;
}

void handle_queries()
{
    int i;
    bool ret;
    for(i = 0; i < m; ++i)
    {
        query_t &q = queries[i];
        if(q.type == SGL)
            ret = handle_single_term_query(q.term[0]);
        else if(q.type == AND)
            ret = handle_and_query(q.term[0], q.term[1]);
        else if(q.type == OR)
            ret = handle_or_query(q.term[0], q.term[1]);
        else
            ret = handle_not_query(q.term[0]);
        if(!ret)
            std::cout << "Sorry, I found nothing.\n";
        std::cout << "==========\n";
    }
}

int main()
{
    int i;
    std::string line;
    std::ios_base::sync_with_stdio(false);
    std::cin >> n;
    std::getline(std::cin, line);
    docs.resize(n);
    for(i = 0; i < n; ++i)
    {
        for(;;)
        {
            std::getline(std::cin, line);
            if(line == "**********")
                break;
            docs[i].push_back(line);
        }
    }
    std::cin >> m;
    std::getline(std::cin, line);
    queries.reserve(m);
    for(i = 0; i < m; ++i)
    {
        std::getline(std::cin, line);
        parse_query(line);
    }
    parse_documents();
    handle_queries();
    return 0;
}

