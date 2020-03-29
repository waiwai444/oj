#include <cstdio>
#include <cctype>

bool prime[1041];

int main()
{
    int i, j;
    char word[21], *p;
    prime[1] = prime[2] = true;
    for(i = 3; i < 1040; i += 2)
        prime[i] = true;
    for(i = 3; i < 520; i += 2)
        if(prime[i])
            for(j = i+i; j <= 1040; j += i)
                if(prime[j])
                    prime[j] = false;
    while(std::scanf("%s", word) != EOF)
    {
        for(i = 0, p = word; *p; ++p)
        {
            if(std::islower(*p))
                i += *p-'a'+1;
            else
                i += *p-'A'+27;
        }
        prime[i] ? std::puts("It is a prime word.") : std::puts("It is not a prime word.");
    }
    return 0;
}
