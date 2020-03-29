#include <stdio.h>
#include <stdlib.h>
#include <queue>

#define INVALID -1

struct binary_tree_node
{
	binary_tree_node* ltree;
	binary_tree_node* rtree;
	int value;
	
	binary_tree_node() : ltree(0), rtree(0), value(INVALID) {}
};

bool create_tree(binary_tree_node *tree, char *node, int *node_num)
{
	int value;
	char *path_ptr, dir;
	bool duplicate = false;
	binary_tree_node *node_ptr;
	*node_num = 0;
	while(node[1] != ')')
	{
		(*node_num)++;
		if(!duplicate)
		{
			value = atoi(&node[1]);
			path_ptr = &node[2];
			while(*path_ptr++ != ',');
			node_ptr = tree;
			while((dir = *path_ptr++) != ')')
			{
				if(dir == 'L')
				{
					if(node_ptr->ltree == 0)
						node_ptr->ltree = new binary_tree_node;
					node_ptr = node_ptr->ltree;
				}
				else
				{
					if(node_ptr->rtree == 0)
						node_ptr->rtree = new binary_tree_node;
					node_ptr = node_ptr->rtree;
				}
			}
			if(node_ptr->value != INVALID)
				duplicate = true;
			else
				node_ptr->value = value;
		}
		scanf("%s", node);
	}
	return !duplicate;
}

void recur_destroy_tree(binary_tree_node *tree)
{
	if(tree->ltree != 0)
	{
		recur_destroy_tree(tree->ltree);
		delete tree->ltree;
	}
	if(tree->rtree != 0)
	{
		recur_destroy_tree(tree->rtree);
		delete tree->rtree;
	}
}

void destroy_tree(binary_tree_node *tree)
{
	tree->value = INVALID;
	tree->ltree = tree->rtree = 0;
	recur_destroy_tree(tree);
}

bool bfs(binary_tree_node *tree, int *result)
{
	int i = 0;
	binary_tree_node *node_ptr;
	std::queue<binary_tree_node*> node_queue;
	node_queue.push(tree);
	while(!node_queue.empty())
	{
		node_ptr = node_queue.front();
		node_queue.pop();
		if(node_ptr->value == INVALID)
			return false;
		result[i++] = node_ptr->value;
		if(node_ptr->ltree != 0)
			node_queue.push(node_ptr->ltree);
		if(node_ptr->rtree != 0)
			node_queue.push(node_ptr->rtree);
	}
	return true;
}

int main()
{
	int i;
	char node[300];
	int node_num;
	int result[256];
	binary_tree_node tree;
	while(scanf("%s", node) != EOF)
	{
		if(create_tree(&tree, node, &node_num) == false)
			printf("not complete\n");
		else if(bfs(&tree, result) == false)
			printf("not complete\n");
		else
		{
			for(i = 0; i < node_num-1; i++)
				printf("%d ", result[i]);
			printf("%d\n", result[i]);
		}
		destroy_tree(&tree);
	}
	return 0;
}
