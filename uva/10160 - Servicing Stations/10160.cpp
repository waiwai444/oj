#include <cstdio>

#define NMAX 35

int n;
struct Station {
	long long dominating_map;	// the dominating bitmap for a station
	int adj_num;	// the number of adjacent stations
} station[NMAX+1];

struct DominatingState {
	long long state;	// current dominating state
	int dnum;	// the size of current dominating set
	int dominating_set[NMAX];	// the current dominating set
};

long long rest_cover[NMAX+1];	// the cover of the rest of stations, inclusively

#define QSIZE 500000
DominatingState dsqueue[QSIZE];
int head, tail;

inline bool finished(long long state)
{
	return state==(((long long)1<<n)-1);
}

int bfs()
{
	int i;
	head = tail = 0;
	DominatingState ds, ds2;
	ds.state = 0;
	ds.dnum = 0;
	dsqueue[tail] = ds;
	tail = (tail+1)%QSIZE;
	while(head!=tail)
	{
		ds = dsqueue[head];
		head = (head+1)%QSIZE;
		for(i=ds.dnum==0?1:ds.dominating_set[ds.dnum-1]+1; i<=n; i++)
		{
			if(!finished(ds.state | rest_cover[i]))
				break;
			if((ds.state & station[i].dominating_map)==station[i].dominating_map)
				continue;
			ds2 = ds;
			ds2.state |= station[i].dominating_map;
			ds2.dominating_set[ds2.dnum++] = i;
			if(finished(ds2.state))
				return ds2.dnum;
			dsqueue[tail] = ds2;
			tail = (tail+1)%QSIZE;
		}
	}
	return -1;
}

int main()
{
	int i, m, s, t;
	while(scanf("%d %d", &n, &m)!=EOF && (n || m))
	{
		for(i=1; i<=n; i++)
		{
			station[i].dominating_map = (long long)1<<(i-1);
			station[i].adj_num = 0;
		}
		for(i=0; i<m; i++)
		{
			scanf("%d %d", &s, &t);
			station[s].dominating_map |= (long long)1<<(t-1);
			station[t].dominating_map |= (long long)1<<(s-1);
			station[s].adj_num++;
			station[t].adj_num++;
		}
		rest_cover[n] = station[n].dominating_map;
		for(i=n-1; i>=1; i--)
			rest_cover[i] = rest_cover[i+1] | station[i].dominating_map;
		printf("%d\n", bfs());
	}
	return 0;
}