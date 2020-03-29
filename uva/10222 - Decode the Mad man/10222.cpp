#include <cstdio>
#include <cctype>

char alpha_map[] = "-czaqsdfyghjbvui-w-etx--r-";

char convert(char c)
{
    if(isalpha(c))
    {
        c = tolower(c);
        return alpha_map[c-'a'];
    }
    else
    {
        switch(c)
        {
        case '[':
        case '{':
            return 'o';
        case ']':
        case '}':
            return 'p';
        case ';':
        case ':':
            return 'k';
        case '\'':
        case '\"':
            return 'l';
        case ',':
        case '<':
            return 'n';
        case '.':
        case '>':
            return 'm';
        }
    }
    return c;
}

int main()
{
    char ch;
    while((ch = getchar()) != EOF)
    {
        printf("%c", convert(ch));
    }
    return 0;
}

