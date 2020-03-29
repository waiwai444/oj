#include <iostream>
#include <string>

int main()
{
    int tc = 0;
    std::string input;
    while(std::getline(std::cin, input))
    {
        if(input == "#")
            break;
        std::cout<<"Case "<<++tc<<": ";
        if(input == "HELLO")
            std::cout<<"ENGLISH";
        else if(input == "HOLA")
            std::cout<<"SPANISH";
        else if(input == "HALLO")
            std::cout<<"GERMAN";
        else if(input == "BONJOUR")
            std::cout<<"FRENCH";
        else if(input == "CIAO")
            std::cout<<"ITALIAN";
        else if(input == "ZDRAVSTVUJTE")
            std::cout<<"RUSSIAN";
        else
            std::cout<<"UNKNOWN";
        std::cout<<std::endl;
    }
    return 0;
}
