#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>

int c, s;
int m[10];
int ch[5][2];
double am;

void solve()
{
    int i, sum;
    sum = 0;
    for(i = 0; i < s; i++)
        sum += m[i];
    am = (double)sum/c;
	
	for(; s < 2*c; s++)
		m[s] = 0;
	std::sort(&m[0], &m[s], std::greater<int>());

	for(i = 0; i < c; i++)
	{
		ch[i][0] = m[i];
		ch[i][1] = m[s-i-1];
	}
}

void print_ans()
{
	int i;
	double imb = 0.0;
	for(i = 0; i < c; i++)
	{
		printf(" %d:", i);
		if(ch[i][0] > 0)
			printf(" %d", ch[i][0]);
		if(ch[i][1] > 0)
			printf(" %d", ch[i][1]);
		printf("\n");
		imb += fabs(ch[i][0]+ch[i][1]-am);
	}
	printf("IMBALANCE = %.5f\n\n", imb);
}

int main()
{
    int i, tc = 0;
    while(scanf("%d%d", &c, &s) != EOF)
    {
        for(i = 0; i < s; i++)
            scanf("%d", &m[i]);
        solve();
		printf("Set #%d\n", ++tc);
		print_ans();
    }
    return 0;
}

