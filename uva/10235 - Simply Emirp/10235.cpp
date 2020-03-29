#include <cstdio>

char type[1000000];

int reverse_number(int n)
{
    int r = 0;
    while(n)
    {
        r = r*10+n%10;
        n /= 10;
    }
    return r;
}

void check_type()
{
    int i, j, k;
    type[2] = 1;
    for(i = 3; i < 1000000; i += 2)
        type[i] = 1;
    for(i = 3; i < 1000000; i += 2)
    {
        if(type[i] > 0)
        {
            for(j = i+i; j < 1000000; j += i)
                type[j] = 0;
            if(type[i] == 1)
            {
                k = reverse_number(i);
                if(k < i && type[k] > 0)
                    type[k] = type[i] = 2;
            }
        }
    }
}

int main()
{
    int n;
    check_type();
    while(std::scanf("%d", &n) != EOF)
    {
        std::printf("%d is ", n);
        switch(type[n])
        {
        case 0:
            std::puts("not prime.");
            break;
        case 1:
            std::puts("prime.");
            break;
        case 2:
            std::puts("emirp.");
            break;
        }
    }
    return 0;
}
