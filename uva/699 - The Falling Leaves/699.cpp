#include <stdio.h>
#include <string.h>

#define TRAVERSE_LEFT 0
#define TRAVERSE_RIGHT 1

int main()
{
	int i, pile[100], left, right, node, tc = 0;
	const int root = 50;
	int pos_stack[100];
	char flag_stack[100];
	int top;
	while(scanf("%d", &node), node != -1)
	{
		memset(pile, 0, sizeof(pile));
		left = right = root;
		top = 0;
		pos_stack[top] = root;
		flag_stack[top++] = TRAVERSE_LEFT;
		pile[root] += node;
		while(top > 0)
		{
			scanf("%d", &node);
			if(node == -1)
			{
				if(flag_stack[top-1] == TRAVERSE_LEFT)
				{
					flag_stack[top-1] = TRAVERSE_RIGHT;
				}
				else
				{
					top--;
					while(top > 0 && flag_stack[top-1] == TRAVERSE_RIGHT)
						top--;
					if(top > 0)
						flag_stack[top-1] = TRAVERSE_RIGHT;
				}
			}
			else
			{
				if(flag_stack[top-1] == TRAVERSE_LEFT)
				{					
					pos_stack[top] = pos_stack[top-1]-1;
					if(pos_stack[top] < left)
						left = pos_stack[top];
				}
				else
				{
					pos_stack[top] = pos_stack[top-1]+1;
					if(pos_stack[top] > right)
						right = pos_stack[top];
				}
				flag_stack[top++] = TRAVERSE_LEFT;
				pile[pos_stack[top-1]] += node;
			}
		}
		printf("Case %d:\n%d", ++tc, pile[left]);
		for(i = left+1; i <= right; i++)
			printf(" %d", pile[i]);
		printf("\n\n");
	}
	return 0;
}