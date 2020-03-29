#include <stdio.h>

struct quad_tree
{
	quad_tree *rt, *lt, *lb, *rb;
	char type;
	int width;
	int black_count;
};

int create_tree(quad_tree tree[], char str[], int pos, int width, int *black_count)
{
	int new_pos;
	tree[pos].type = str[pos];
	tree[pos].width = width;
	if(str[pos] == 'p')
	{
		int bc;
		tree[pos].rt = &tree[pos+1];
		new_pos = create_tree(tree, str, pos+1, width/2, &bc);
		tree[pos].black_count = bc;
		tree[pos].lt = &tree[new_pos];
		new_pos = create_tree(tree, str, new_pos, width/2, &bc);
		tree[pos].black_count += bc;
		tree[pos].lb = &tree[new_pos];
		new_pos = create_tree(tree, str, new_pos, width/2, &bc);
		tree[pos].black_count += bc;
		tree[pos].rb = &tree[new_pos];
		new_pos = create_tree(tree, str, new_pos, width/2, &bc);
		tree[pos].black_count += bc;
		*black_count = tree[pos].black_count;
		return new_pos;
	}
	else
	{
		*black_count = tree[pos].black_count = str[pos] == 'f' ? width*width : 0;
		return pos+1;
	}
}

quad_tree tree1[1500], tree2[1500];

int count_black(quad_tree *tree_node1, quad_tree *tree_node2)
{
	if(tree_node1->type == 'f')
		return tree_node1->width*tree_node1->width;
	if(tree_node2->type == 'f')
		return tree_node2->width*tree_node2->width;
	if(tree_node1->type == 'e')
		return tree_node2->black_count;
	if(tree_node2->type == 'e')
		return tree_node1->black_count;
	int sum = count_black(tree_node1->rt, tree_node2->rt);
	sum += count_black(tree_node1->lt, tree_node2->lt);
	sum += count_black(tree_node1->lb, tree_node2->lb);
	sum += count_black(tree_node1->rb, tree_node2->rb);
	return sum;
}

int main()
{
	int tc, bc;
	char str1[1500], str2[1500];
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s%s", str1, str2);
		create_tree(tree1, str1, 0, 32, &bc);
		create_tree(tree2, str2, 0, 32, &bc);
		printf("There are %d black pixels.\n", count_black(tree1, tree2));
	}
	return 0;
}