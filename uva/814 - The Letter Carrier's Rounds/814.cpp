#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

std::map<std::string, std::set<std::string> > mtas;
std::string sender_mta, sender_name;
std::vector<std::vector<std::string> > recvs;
std::map<std::string, int> recv_mta_idx;
std::set<std::string> recv_email_set;
std::vector<std::string> msg;

inline void parse_email(const std::string &email, std::string *user, std::string *mta)
{
    int i = email.find_first_of('@');
    *user = email.substr(0, i);
    *mta = email.substr(i+1);
}

int main()
{
    int i, j, n;
    std::string tag, mta_name, user_name, email, line;
    std::map<std::string, int>::iterator it_msi;
    std::ios_base::sync_with_stdio(false);
    while(std::cin >> tag)
    {
        if(tag[0] == '*')
            break;
        std::cin >> mta_name >> n;
        mtas[mta_name] = std::set<std::string>();
        std::set<std::string> &users = mtas[mta_name];
        for(i = 0; i < n; ++i)
        {
            std::cin >> user_name;
            users.insert(user_name);
        }
    }
    for(;;)
    {
        std::cin >> email;
        if(email[0] == '*')
            break;
        parse_email(email, &sender_name, &sender_mta);
        recvs.clear();
        recv_mta_idx.clear();
        recv_email_set.clear();
        while(std::cin >> email)
        {
            if(email[0] == '*')
                break;
            if(!recv_email_set.insert(email).second)
                continue;
            parse_email(email, &user_name, &mta_name);
            if((it_msi = recv_mta_idx.find(mta_name)) != recv_mta_idx.end())
                recvs[it_msi->second].push_back(user_name);
            else
            {
                i = recvs.size();
                recvs.push_back(std::vector<std::string>(1, mta_name));
                recvs[i].push_back(user_name);
                recv_mta_idx[mta_name] = i;
            }
        }
        msg.clear();
        std::getline(std::cin, line);
        while(std::getline(std::cin, line))
        {
            if(line[0] == '*')
                break;
            msg.push_back(line);
        }
        for(i = 0; i < recvs.size(); ++i)
        {
            std::cout << "Connection between " << sender_mta << " and " << recvs[i][0] << '\n';
            std::cout << "     HELO " << sender_mta << '\n';
            std::cout << "     250\n";
            std::cout << "     MAIL FROM:<" << sender_name << '@' << sender_mta << ">\n";
            std::cout << "     250\n";
            std::set<std::string> &user_set = mtas[recvs[i][0]];
            n = 0;
            for(j = 1; j < recvs[i].size(); ++j)
            {
                std::cout << "     RCPT TO:<" << recvs[i][j] << '@' << recvs[i][0] << ">\n";
                if(user_set.find(recvs[i][j]) != user_set.end())
                {
                    std::cout << "     250\n";
                    ++n;
                }
                else
                    std::cout << "     550\n";
            }
            if(n)
            {
                std::cout << "     DATA\n";
                std::cout << "     354\n";
                for(j = 0; j < msg.size(); ++j)
                    std::cout << "     " << msg[j] << '\n';
                std::cout << "     .\n";
                std::cout << "     250\n";
            }
            std::cout << "     QUIT\n";
            std::cout << "     221\n";
        }
    }
    return 0;
}

