#include <cstdio>

long long n;
int part[20], np;
const char *txt[] = { "shata", "hajar", "lakh", "kuti" };
const int step[] = { 100, 10, 100, 100 };

void convert()
{
	part[0] = n%step[0];
	n /= step[0];
	np = 1;
	while(n)
	{
		part[np] = n%step[np%4];
		n /= step[np%4];
		++np;
	}
}

void print_ans()
{
	int i;
	for(i = np-1; i > 0; i--)
	{
		if(part[i] > 0)
			printf(" %d %s", part[i], txt[(i-1)%4]);
		else if(i%4 == 0)
			printf(" %s", txt[3]);
	}
	if(np == 1 || part[0] > 0)
		printf(" %d\n", part[0]);
	else
		printf("\n");
}

int main()
{
	int c = 0;
	while(scanf("%lld", &n) != EOF)
	{
		convert();
		printf("%4d.", ++c);
		print_ans();
	}
	return 0;
}

