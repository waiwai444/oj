#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fstream>

int n;
int parts[64];
bool in_stack[64];
int stack[64];
int sum[64];
int stack_size;

//std::ofstream fout;

int cmp(const void *a, const void *b)
{
	return *(int *)b-*(int *)a;
}

inline void push(int i, int s)
{
	stack[stack_size] = i;
	sum[stack_size] = s;
	in_stack[i] = true;
	stack_size++;
}

inline int pop()
{
	int prev = stack[stack_size-1];
	in_stack[prev] = false;
	stack_size--;
	return prev;
}

inline int reseek()
{
	int i;
	for(i=1; i<n; i++)
	{
		if(in_stack[i]==false)
			return i;
	}
	return n;
}

int main()
{
	int i, j, k;
	int total_len;
	int min_len;
	int prev;
	int next;
	//fout.open("out");
	while(true)
	{
		scanf("%d", &n);
		if(n==0)
			break;
		total_len = 0;
		for(i=0; i<n; i++)
		{
			scanf("%d", &parts[i]);
			total_len += parts[i];
		}
		qsort(parts, n, sizeof(int), cmp);

		min_len = 0;
		for(i=parts[0]; i<=total_len/2; i++) 
		{
			if(total_len%i!=0)
				continue;
			memset(in_stack, false, 64*sizeof(bool));
			stack_size = 0;
			next = 0;
			while(true)
			{
				// push
				if(next==0 || sum[stack_size-1]==i)
				{
					push(next, parts[next]);
					/*fout<<next<<": "<<parts[next]<<"        "<<sum[stack_size-1]<<"\t\t";
					for(k=0; k<stack_size; k++)
						fout<<stack[k]<<' ';
					fout<<std::endl;*/
				}
				else
				{
					push(next, sum[stack_size-1]+parts[next]);
					/*fout<<next<<": "<<parts[next]<<"        "<<sum[stack_size-1]<<"\t\t";
					for(k=0; k<stack_size; k++)
						fout<<stack[k]<<' ';
					fout<<std::endl;*/
				}
								
				// find the next
				if(sum[stack_size-1]==i)
				{
					if(stack_size==n)
					{
						min_len = i; 
						break;
					}
					else
					{
						next = reseek();
						continue;
					}
				}
				else if(i-sum[stack_size-1]<parts[n-1])
					next = n;
				else
				{
					next++;
					while(next<n && (sum[stack_size-1]+parts[next]>i || in_stack[next]))
						next++;
				}

				while(next==n)
				{
					prev = pop();
					if(stack_size==0)
						break;
					while(sum[stack_size-1]==i)	// pop the last two elements of the previous stick
					{
						prev = pop();
						if(stack_size==0)
							break;
						if(sum[stack_size-1]!=i)
						{
							prev = pop();
							if(stack_size==0)
								break;
						}
					}
					if(stack_size==0)
						break;
					next = prev+1;
					if(parts[n-1]==parts[prev])
						next = n;
					else
						while(next<n && (sum[stack_size-1]+parts[next]>i || parts[next]==parts[prev] || in_stack[next]))
							next++;
				}
				if(stack_size==0)
					break;
				
			}
			if(min_len>0)
				break;
		}
		if(min_len==0)
			min_len = total_len;
		printf("%d\n", min_len);
	}
	return 0;
}
