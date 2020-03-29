#include <stdio.h>
#include <vector>

#define MAX 730

bool happy[730];
bool visited[730];
std::vector<int> path;

int ssd(int n)
{
	int s = 0, d;
	while(n)
	{
		d = n%10;
		s += d*d;
		n /= 10;
	}
	return s;
}

int main()
{
	int i, c, tc, n, m;
	scanf("%d", &tc);
	visited[1] = happy[1] = true;
	for(c = 1; c <= tc; c++)
	{
		scanf("%d", &n);
		path.clear();
		m = n;
		if(m >= MAX)
			m = ssd(m);
		while(!visited[m])
		{
			visited[m] = true;
			path.push_back(m);
			m = ssd(m);
		}
		if(happy[m])
			for(i = 0; i < path.size(); i++)
				happy[path[i]] = happy[m];
		printf("Case #%d: %d is %s number.\n", c, n, happy[m] ? "a Happy" : "an Unhappy");
	}
	return 0;
}