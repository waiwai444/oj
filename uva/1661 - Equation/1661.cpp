#include <cstdio>
#include <cstring>
#include <cctype>

int nn;
bool none, multi;

struct frac_t
{
	long long n, d;
} ans;

struct node_t
{
	char ch;
	node_t *lch, *rch;
	frac_t val;
} nodes[30];

int stack[30];
int top;

long long gcd(long long x, long long y)
{
	return y == 0 ? x : gcd(y, x%y);
}

void evaluate(char ch, const frac_t &v1, const frac_t &v2, frac_t *res)
{
	if(ch == '+')
	{
		res->n = v1.n*v2.d+v2.n*v1.d;
		res->d = v1.d*v2.d;
	}
	if(ch == '-')
	{
		res->n = v1.n*v2.d-v2.n*v1.d;
		res->d = v1.d*v2.d;
	}
	if(ch == '*')
	{
		res->n = v1.n*v2.n;
		res->d = v1.d*v2.d;
	}
	if(ch == '/')
	{
		res->n = v1.n*v2.d;
		res->d = v1.d*v2.n;
	}
}

bool create_etree(char *str)
{
	nn = top = 0;
	char *ch = strtok(str, " ");
	while(ch)
	{
		if(isdigit(*ch))
		{
			nodes[nn].ch = 'N';
			nodes[nn].val.n = *ch-'0', nodes[nn].val.d = 1;
			nodes[nn].lch = nodes[nn].rch = NULL;
			stack[top++] = nn;
		}
		else if(*ch == 'X')
		{
			nodes[nn].ch = 'X';
			nodes[nn].lch = nodes[nn].rch = NULL;
			stack[top++] = nn;
		}
		else if(*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/')
		{
			node_t &nl = nodes[stack[top-2]], &nr = nodes[stack[top-1]];
			if(*ch == '/' && nr.ch == 'N' && nr.val.n == 0)
			{
				none = true;
				return false;
			}
			nodes[nn].lch = &nl;
			nodes[nn].rch = &nr;
			if(nl.ch == 'N' && nr.ch == 'N')
			{
				evaluate(*ch, nl.val, nr.val, &nodes[nn].val);
				nodes[nn].ch = 'N';
			}
			else if(*ch == '*' && (nl.ch == 'N' && nl.val.n == 0 || nr.ch == 'N' && nr.val.n == 0)
					|| *ch == '/' && nl.ch == 'N' && nl.val.n == 0)
			{
				nodes[nn].val.n = 0, nodes[nn].val.d = 1;
				nodes[nn].ch = 'N';
			}
			else
				nodes[nn].ch = *ch;
			stack[top-2] = nn;
			--top;
		}
		++nn;
		ch = strtok(NULL, " ");
	}
	return true;
}

void evaluate_x(node_t *pn)
{
	frac_t r;
	ans.n = 0, ans.d = 1;
	if(pn->ch == 'N')
	{
		if(pn->val.n == 0)
			multi = true;
		else
			none = true;
		return;
	}
	while(pn->ch != 'X')
	{
		r = ans;
		if(pn->ch == '+')
		{
			if(pn->lch->ch == 'N')
				evaluate('-', r, pn->lch->val, &ans);
			else
				evaluate('-', r, pn->rch->val, &ans);
		}
		else if(pn->ch == '-')
		{
			if(pn->lch->ch == 'N')
				evaluate('-', pn->lch->val, r, &ans);
			else
				evaluate('+', pn->rch->val, r, &ans);
		}
		else if(pn->ch == '*')
		{
			if(pn->lch->ch == 'N')
				evaluate('/', r, pn->lch->val, &ans);
			else
				evaluate('/', r, pn->rch->val, &ans);
		}
		else if(pn->ch == '/')
		{
			if(pn->lch->ch == 'N')
			{
				if(r.n == 0)
				{
					none = true;
					return;
				}
				evaluate('/', pn->lch->val, r, &ans);
			}
			else
				evaluate('*', pn->rch->val, r, &ans);
		}
		if(pn->lch->ch == 'N')
			pn = pn->rch;
		else
			pn = pn->lch;
	}
	int g = gcd(ans.n, ans.d);
	ans.n /= g, ans.d /= g;
	if(ans.d < 0)
		ans.n = -ans.n, ans.d = -ans.d;
}

int main()
{
	char buf[100];
	while(fgets(buf, sizeof(buf), stdin))
	{
		none = multi = false;
		if(create_etree(buf))
			evaluate_x(&nodes[nn-1]);
		if(none)
			printf("NONE\n");
		else if(multi)
			printf("MULTIPLE\n");
		else
			printf("X = %lld/%lld\n", ans.n, ans.d);
	}
	return 0;
}

