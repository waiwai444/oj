#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int node_num;
int inorder[10001], postorder[10001];
char input[50001];

int traverse(int in_begin, int in_end, int post_begin, int post_end, int *cur_sum)
{
	int i, root = postorder[post_end];
	if(in_begin == in_end)	// leaf
	{
		return *cur_sum = inorder[in_begin];
	}
	for(i = in_begin; i <= in_end; i++)
		if(inorder[i] == root)
			break;	
	int s1, s2, ret1, ret2;
	if(i == in_begin)
	{
		ret2 = traverse(in_begin+1, in_end, post_begin, post_end-1, &s2);
		*cur_sum = s2+root;
		return ret2;
	}
	else if(i == in_end)
	{
		ret1 = traverse(in_begin, in_end-1, post_begin, post_end-1, &s1);
		*cur_sum = s1+root;
		return ret1;
	}
	else
	{
		ret1 = traverse(in_begin, i-1, post_begin, post_begin+(i-1-in_begin), &s1);
		ret2 = traverse(i+1, in_end, post_end-in_end+i, post_end-1, &s2);
		if(s1 < s2)
		{
			*cur_sum = s1+root;
			return ret1;
		}
		else if(s1 > s2)
		{
			*cur_sum = s2+root;
			return ret2;
		}
		else
		{
			*cur_sum = s1+root;
			return ret1 < ret2 ? ret1 : ret2;
		}
	}
}

int main()
{
	int i, min_sum;
	char *ptr1, *ptr2;
	while(fgets(input, sizeof(input), stdin))
	{
		ptr1 = input;
		for(node_num = 0; (inorder[node_num] = (int)strtol(ptr1, &ptr2, 10)) != 0; node_num++, ptr1 = ptr2);
		fgets(input, sizeof(input), stdin);
		ptr1 = input;
		for(i = 0; (postorder[i] = (int)strtol(ptr1, &ptr2, 10)) != 0; i++, ptr1 = ptr2);
		printf("%d\n", traverse(0, node_num-1, 0, node_num-1, &min_sum));
	}
	return 0;
}
