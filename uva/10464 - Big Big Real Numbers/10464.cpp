#include <cstdio>
#include <cstring>

char nstr1[2002], nstr2[2002];

class bignum_t
{
public:
    bignum_t()
        : sign(1)
    {
        memset(inte, 0, sizeof(inte));
        memset(frac, 0, sizeof(frac));
        ni = nf = 0;
    }

    friend bool abs_less(const bignum_t &x, const bignum_t &y);
    friend void add_by(bignum_t &x, const bignum_t &y);
    friend void unsigned_sub_by(bignum_t &x, const bignum_t &y);
    friend void unsigned_sub_by_rev(bignum_t &x, const bignum_t &y);

    friend bignum_t str_to_bignum(const char *str);
    friend void print_bignum(const bignum_t &n);

private:
    int sign;
    int ni, nf;
    signed char inte[1001];
    signed char frac[1000];

};

bool abs_less(const bignum_t &x, const bignum_t &y)
{
    if(x.ni != y.ni)
        return x.ni < y.ni;
    for(int i = x.ni-1; i >= 0; i--)
        if(x.inte[i] != y.inte[i])
            return x.inte[i] < y.inte[i];
    return memcmp(&x.frac, &y.frac, sizeof(x.frac)) < 0;
}

void add_by(bignum_t &x, const bignum_t &y)
{
    if(x.sign == y.sign)
    {
        int i;
        char c = 0;
        if(y.nf > x.nf) x.nf = y.nf;
        for(i = x.nf-1; i >= 0; i--)
        {
            x.frac[i] += y.frac[i]+c;
            if(x.frac[i] >= 10)
            {
                x.frac[i] -= 10;
                c = 1;
            }
            else
                c = 0;
        }
        while(x.nf > 0 && x.frac[x.nf-1] == 0) --x.nf;
        if(y.ni > x.ni) x.ni = y.ni;
        for(i = 0; i < x.ni; i++)
        {
            x.inte[i] += y.inte[i]+c;
            if(x.inte[i] >= 10)
            {
                x.inte[i] -= 10;
                c = 1;
            }
            else
                c = 0;
        }
        if(c) x.inte[x.ni++] = 1;
    }
    else
    {
        if(abs_less(y, x)) // |x| > |y|
        {
            if(x.sign < 0)
            {
                x.sign = 1;
                unsigned_sub_by(x, y);
                x.sign = -1;
            }
            else
                unsigned_sub_by(x, y);
        }
        else
        {
            if(x.sign < 0)
            {
                x.sign = 1;
                unsigned_sub_by_rev(x, y);
            }
            else
            {
                bignum_t *py = const_cast<bignum_t *>(&y);
                py->sign = 1;
                unsigned_sub_by_rev(x, y);
                x.sign = py->sign = -1;
            }
        }
    }
    if(x.nf == 0 && x.ni == 0 && x.sign < 0)
        x.sign = 1;
}

void unsigned_sub_by(bignum_t &x, const bignum_t &y) // x <- x-y (x>y)
{
    int i;
    char c = 0;
    if(y.nf > x.nf) x.nf = y.nf;
    for(i = x.nf-1; i >= 0; i--)
    {
        x.frac[i] -= y.frac[i]+c;
        if(x.frac[i] < 0)
        {
            x.frac[i] += 10;
            c = 1;
        }
        else
            c = 0;
    }
    while(x.nf > 0 && x.frac[x.nf-1] == 0) --x.nf;
    for(i = 0; i < x.ni; i++)
    {
        x.inte[i] -= y.inte[i]+c;
        if(x.inte[i] < 0)
        {
            x.inte[i] += 10;
            c = 1;
        }
        else
            c = 0;
    }
    while(x.ni > 0 && x.inte[x.ni-1] == 0) --x.ni;
}

void unsigned_sub_by_rev(bignum_t &x, const bignum_t &y) // x <- y-x (y>x)
{
    int i;
    char c = 0;
    if(y.nf > x.nf) x.nf = y.nf;
    for(i = x.nf-1; i >= 0; i--)
    {
        x.frac[i] = y.frac[i]-x.frac[i]-c;
        if(x.frac[i] < 0)
        {
            x.frac[i] += 10;
            c = 1;
        }
        else
            c = 0;
    }
    while(x.nf > 0 && x.frac[x.nf-1] == 0) --x.nf;
    x.ni = y.ni;
    for(i = 0; i < x.ni; i++)
    {
        x.inte[i] = y.inte[i]-x.inte[i]-c;
        if(x.inte[i] < 0)
        {
            x.inte[i] += 10;
            c = 1;
        }
        else
            c = 0;
    }
    while(x.ni > 0 && x.inte[x.ni-1] == 0) --x.ni;
}

bignum_t str_to_bignum(const char *str)
{
    bignum_t res;
    const char *p = str, *b = str, *q;
    if(*p == '-')
    {
        res.sign = -1;
        ++p, ++b;
    }
    while(*p && *p != '.')
        ++p;
    res.ni = p-b;
    for(q = p-1; q >= b; q--)
        res.inte[p-q-1] = *q-'0';
    while(res.ni > 0 && res.inte[res.ni-1] == 0)
        --res.ni;
    if(*p)
    {
        for(++p; *p; ++p)
            res.frac[res.nf++] = *p-'0';
        while(res.nf > 0 && res.frac[res.nf-1] == 0)
            --res.nf;
    }
    if(res.ni == 0 && res.nf == 0 && res.sign < 0)
        res.sign = 1;
    return res;
}

char buf[2005];

void print_bignum(const bignum_t &n)
{
    int i;
    char *p = buf;
    if(n.sign < 0)
        *p++ = '-';
    if(n.ni == 0)
        *p++ = '0';
    else
    {
        for(i = n.ni-1; i >= 0; i--)
            *p++ = n.inte[i]+'0';
    }
    *p++ = '.';
    if(n.nf == 0)
        *p++ = '0';
    else
    {
        for(i = 0; i < n.nf; i++)
            *p++ = n.frac[i]+'0';
    }
    *p = 0;
    printf("%s", buf);
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%s%s", nstr1, nstr2);
        bignum_t x = str_to_bignum(nstr1);
        bignum_t y = str_to_bignum(nstr2);
        add_by(x, y);
        print_bignum(x);
        printf("\n");
    }
    return 0;
}

