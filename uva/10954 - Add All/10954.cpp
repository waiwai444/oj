#include <stdio.h>
#include <algorithm>

int n;
int num[5000], head;
long long queue[5000];
int front, back;

void solve()
{
	long long sum, tmp;
	std::sort(num, num+n);
	sum = queue[0] = num[0]+num[1];
	front = 0;
	back = 1;
	head = 2;
	while(head < n || front < back-1)
	{
		if(head == n)
		{
			tmp = queue[front]+queue[front+1];
			front += 2;
		}
		else
		{
			if(num[head] < queue[front])
			{
				if(head == n-1 || num[head+1] >= queue[front])
				{
					tmp = num[head]+queue[front];
					head++;
					front++;
				}
				else
				{
					tmp = num[head]+num[head+1];
					head += 2;
				}
			}
			else if(num[head] > queue[front])
			{
				if(front == back-1 || queue[front+1] >= num[head])
				{
					tmp = num[head]+queue[front];
					head++;
					front++;
				}
				else
				{
					tmp = queue[front]+queue[front+1];
					front += 2;
				}
			}
			else
			{
				tmp = num[head]+queue[front];
				head++;
				front++;
			}
		}
		sum += queue[back++] = tmp;
	}
	printf("%lld\n", sum);
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &num[i]);
		solve();
	}
	return 0;
}
