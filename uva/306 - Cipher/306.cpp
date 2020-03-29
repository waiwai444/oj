#include <cstdio>
#include <cstring>

using namespace std;

int n;
int p[200];
int iter;
char msg[201];
char cipher[201];

int chain[200];

struct chain_info_t
{
	int len;
	int head;
	int pos;
} chain_info[200];

void construct_chains()
{
	int i, j, k, l, head, len;
	bool flag[200];
	memset(flag, false, sizeof(flag));
	for(i = 0, k = 0; i < n; i++)
	{
		if(flag[i])
			continue;
		j = i;
		head = k;
		while(!flag[j])
		{
			flag[j] = true;
			chain[k] = j;
			chain_info[j].head = head;
			chain_info[j].pos = k-head;
			k++;
			j = p[j];
		}
		len = k-head;
		l = len;
		j = i;
		while(l--)
		{
			chain_info[j].len = len;
			j = p[j];
		}
	}
}

size_t getl(char *buf, size_t size)
{
	fgets(buf, size, stdin);
	size_t l = strlen(buf);
	while(buf[l-1] == '\n' || buf[l-1] == '\r')
		buf[--l] = 0;
	return l;
}

void solve()
{
	int i, pos;
	for(i = 0; i < n; i++)
	{
		pos = chain[chain_info[i].head+(chain_info[i].pos+iter)%chain_info[i].len];
		cipher[pos] = msg[i];
	}
	cipher[n] = 0;
}

int main()
{
	int i;
	char tmp[205];
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
		{
			scanf("%d", &p[i]);
			--p[i];
		}
		construct_chains();
		while(scanf("%d", &iter), iter)
		{
			memset(msg, ' ', sizeof(msg));
			scanf("%*c");
			int l = getl(tmp, sizeof(tmp));
			memcpy(msg, tmp, l);
			solve();
			printf("%s\n", cipher);
		}
		printf("\n");
	}
	return 0;
}
