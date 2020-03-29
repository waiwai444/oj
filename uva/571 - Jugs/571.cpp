#include <stdio.h>

#define A 'A'
#define B 'B'

int ca, cb, n;

inline void fill(char ch)
{
	printf("fill %c\n", ch);
}

inline void empty(char ch)
{
	printf("empty %c\n", ch);
}

inline void pour(char ch1, char ch2)
{
	printf("pour %c %c\n", ch1, ch2);
}

inline void success()
{
	printf("success\n");
}

void solve()
{
	int b;
	if(n%ca == cb%ca)
	{
		fill(B);
		b = cb;
		while(n < b)
		{
			b -= ca;
			pour(B, A);
			empty(A);
		}
	}
	else // common case since ca and cb are coprime
	{
		b = 0;
		while(b != n)
		{
			fill(A);
			pour(A, B);
			if(b+ca > cb)
			{
				empty(B);
				pour(A, B);
				b = ca-(cb-b);
			}
			else
				b += ca;
		}
	}
	success();
}

int main()
{
	while(scanf("%d%d%d", &ca, &cb, &n) != EOF)
	{
		solve();
	}
	return 0;
}
