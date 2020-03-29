#include <stdio.h>
#include <map>

using namespace std;

map<int, map<int, int> > data;

int main()
{
	int i, n, f, t, c;
	map<int, map<int, int> >::iterator it1, it3;
	map<int, int>::iterator it2, it4;
	while(scanf("%d", &n), n)
	{
		data.clear();
		for(i = 0; i < n; i++)
		{
			scanf("%d%d", &f, &t);
			data[f][t]++;
		}
		if(n&1)
			goto failed;
		for(it1 = data.begin(); it1 != data.end(); ++it1)
		{
			for(it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
			{
				f = it1->first;
				t = it2->first;
				c = it2->second;
				if((it3 = data.find(t)) == data.end())
					goto failed;
				if((it4 = it3->second.find(f)) == it3->second.end())
					goto failed;
				if(it4->second != c)
					goto failed;
			}
		}
		printf("YES\n");
		continue;
failed:
		printf("NO\n");
	}
	return 0;
}
