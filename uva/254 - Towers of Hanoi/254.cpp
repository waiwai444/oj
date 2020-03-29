#include <cstdio>
#include <cstring>

#define DMAX 31

using namespace std;

struct bigint_t
{
	char v[DMAX];
	int l;
};

int n;
bigint_t m;
bigint_t moves[101];
int peg[3];

void init()
{
	int i, j;
	moves[1].v[0] = moves[1].l = 1;
	for(i = 2; i <= 100; i++)
	{
		char c = 0;
		for(j = 0; j < moves[i-1].l; j++)
		{
			moves[i].v[j] = moves[i-1].v[j]*2+c;
			if(moves[i].v[j] >= 10)
			{
				moves[i].v[j] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		if(c)
			moves[i].v[j++] = c;
		moves[i].l = j;
		moves[i].v[0] += 1;
	}
}

void convert_m(const char *t)
{
	int i, l = strlen(t);
	for(i = 0; i < l; i++)
		m.v[i] = t[l-i-1]-'0';
	m.l = l;
}

inline bool is_zero(const bigint_t &x)
{
	return x.l == 0 || (x.l == 1 && x.v[0] == 0);
}

int compare(const bigint_t &x, const bigint_t &y)
{
	if(x.l > y.l) return 1;
	if(x.l < y.l) return -1;
	for(int i = x.l-1; i >= 0; i--)
	{
		if(x.v[i] < y.v[i])
			return -1;
		if(x.v[i] > y.v[i])
			return 1;
	}
	return 0;
}

void subtract(bigint_t &x, const bigint_t &y)
{
	int i;
	char c = 0;
	for(i = 0; i < y.l; i++)
	{
		x.v[i] = x.v[i]-y.v[i]-c;
		if(x.v[i] < 0)
		{
			x.v[i] += 10;
			c = 1;
		}
		else
			c = 0;
	}
	if(c)
	{
		for(; i < DMAX; i++)
		{
			x.v[i] -= 1;
			if(x.v[i] >= 0)
				break;
			x.v[i] += 10;
		}
	}
	while(x.l > 0 && x.v[x.l-1] == 0)
		--x.l;
}

void solve()
{
	int low, high, mid;
	int cp = 0, np;
	peg[0] = n;
	peg[1] = peg[2] = 0;
	low = 1, high = n;
	while(!is_zero(m))
	{
		while(low <= high)
		{
			mid = (low+high)/2;
			int cmp = compare(m, moves[mid]);
			if(cmp == 0)
			{
				np = (cp+((mid&1)?1:2))%3;
				peg[cp] -= mid;
				peg[np] += mid;
				subtract(m, moves[mid]);
				break;
			}
			else if(cmp > 0)
				low = mid+1;
			else
				high = mid-1;
		}
		if(low > high)
		{
			np = (cp+((high&1)?1:2))%3;
			peg[cp] -= high+1;
			peg[np] += high;
			++peg[3-cp-np];
			subtract(m, moves[high]);
			subtract(m, moves[1]);
			cp = np;
			low = 1;
		}
	}
}

int main()
{
	char tmp[DMAX+1];
	init();
	while(scanf("%d", &n))
	{
		scanf("%s", tmp);
		if(n == 0)
			break;
		convert_m(tmp);
		solve();
		printf("%d %d %d\n", peg[0], peg[1], peg[2]);
	}
	return 0;
}

