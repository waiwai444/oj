#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define MAXN 100
#define MAXK 10
#define INF 0x3f3f3f3f

int A, B, L, K;
struct adj_t
{
	int v, d;
};
std::vector<adj_t> adj[MAXN+1];

int dp[MAXN+1][MAXN+1];
std::vector<int> sup[MAXN+1];
int dist[MAXN+1][MAXK+1];
bool vis[MAXN+1][MAXK+1];

struct q_elem
{
	int v, k, d;
};

struct comparator
{
	bool operator()(const q_elem &e1, const q_elem &e2)
	{
		return e1.d > e2.d;
	}
};

int solve()
{
	int i, j, k;
	memset(dp, INF, sizeof(dp));
	for(i = 1; i <= A+B; i++)
	{
		dp[i][i] = 0;
		for(j = 0; j < adj[i].size(); j++)
		{
			adj_t &a = adj[i][j];
			dp[i][a.v] = dp[a.v][i] = a.d;
		}
	}
	for(k = 1; k <= A; k++)
	{
		for(i = 1; i < A+B; i++)
		{
			for(j = i+1; j <= A+B; j++)
			{
				if(dp[i][j] > dp[i][k]+dp[k][j])
					dp[i][j] = dp[j][i] = dp[i][k]+dp[k][j];
			}
		}
	}
	for(i = 1; i < A+B; i++)
		for(j = i+1; j <= A+B; j++)
			if(dp[i][j] <= L)
			{
				sup[i].push_back(j);
				sup[j].push_back(i);
			}

	memset(dist, INF, sizeof(dist));
	memset(vis, false, sizeof(vis));
	std::priority_queue<q_elem, std::vector<q_elem>, comparator> q;
	q_elem e, e2;
	e.v = A+B, e.k = 0, e.d = 0;
	q.push(e);
	dist[A+B][0] = 0;
	while(!q.empty())
	{
		e = q.top(), q.pop();
		if(vis[e.v][e.k])
			continue;
		vis[e.v][e.k] = true;
		for(i = 0; i < adj[e.v].size(); i++)
		{
			adj_t &a = adj[e.v][i];
			if(dist[a.v][e.k] > dist[e.v][e.k]+a.d)
			{
				dist[a.v][e.k] = dist[e.v][e.k]+a.d;
				e2.v = a.v, e2.k = e.k, e2.d = dist[a.v][e.k];
				q.push(e2);
			}
		}
		if(e.k < K)
		{
			for(i = 0; i < sup[e.v].size(); i++)
			{
				j = sup[e.v][i];
				if(dist[j][e.k+1] > dist[e.v][e.k])
				{
					dist[j][e.k+1] = dist[e.v][e.k];
					e2.v = j, e2.k = e.k+1, e2.d = dist[j][e.k+1];
					q.push(e2);
				}
			}
		}
	}

	int ans = INF;
	for(i = 0; i <= K; i++)
		if(dist[1][i] < ans)
			ans = dist[1][i];
	return ans;
}

int main()
{
	int i, tc, M, x, y, l;
	adj_t a;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d%d%d%d", &A, &B, &M, &L, &K);
		for(i = 1; i <= A+B; i++)
		{
			adj[i].clear();
			sup[i].clear();
		}
		for(i = 0; i < M; i++)
		{
			scanf("%d%d%d", &x, &y, &l);
			a.v = y, a.d = l;
			adj[x].push_back(a);
			a.v = x;
			adj[y].push_back(a);
		}
		printf("%d\n", solve());
	}
	return 0;
}

