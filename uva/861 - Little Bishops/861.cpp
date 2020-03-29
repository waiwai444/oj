#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX 16
#define NMAX 9

void get_candidates(int solution[], int d, int n, int k, int candidates[], int &ncandidates)
{
	bool flag[NMAX];
    std::fill(flag, flag+NMAX, true);
	int i, j;
	int b = d<=n?d:(n<<1)-d;
	for(i=(d&1)==0?2:1; i<d; i+=2)
	{
		if(solution[i]==0)
			continue;
		if(d<=n)
		{
			j = solution[i]+((d-i)>>1);
			if(j>0 && j<=b)
				flag[j] = false;
		}
		else if(i<n)
		{
			j = solution[i]+(((n<<1)-i-d)>>1);
			if(j>0 && j<=b)
				flag[j] = false;
		}
		else
		{
			j = solution[i]-((d-i)>>1);
			if(j>0 && j<=b)
				flag[j] = false;
		}
	}
	ncandidates = 0;
	for(i=1; i<=b; i++)
		if(flag[i])
			candidates[ncandidates++] = i;
}

int backtrack(int solution[], int d, int n, int k)
{
	int i;
	int sum;
	int candidates[NMAX];
	int ncandidates;
	if(k==0)
		return 1;
	if((d&1)==0 && n-(d>>1)<k || (d&1)==1 && n-((d+1)>>1)+1<k)
		return 0;
	if((d&1)==0 && n-(d>>1)>k || (d&1)==1 && n-((d+1)>>1)+1>k)
	{
		solution[d] = 0;
		sum = backtrack(solution, d+2, n, k);
	}
	else
		sum = 0;
	get_candidates(solution, d, n, k, candidates, ncandidates);
	for(i=0; i<ncandidates; i++)
	{
		solution[d] = candidates[i];
		sum += backtrack(solution, d+2, n, k-1);
	}
	return sum;
}

int main()
{
	int i, n, k;
	int solution[MAX];
	int sum;
	while(scanf("%d %d", &n, &k)!=EOF && (n || k))
	{
		if(k==0)
			printf("1\n");
		else if(k==1)
			printf("%d\n", n*n);
		else if(k>=n+n-1)
			printf("0\n");
		else
		{
			sum = 0;
			for(i=0; i<=k; i++)
				sum += backtrack(solution, 1, n, i)*backtrack(solution, 2, n, k-i);
			printf("%d\n", sum);
		}
	}
	return 0;
}
