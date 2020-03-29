#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

int n;
string num[50];

bool cmp(const string &n1, const string &n2)
{
	return n1+n2 > n2+n1;
}

int main()
{
	int i;
	char input[100];
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
		{
			scanf("%s", input);
			num[i] = input;
		}
		sort(num, num+n, cmp);
		for(i = 0; i < n; i++)
			printf("%s", num[i].c_str());
		printf("\n");
	}
	return 0;
}
