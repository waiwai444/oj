#include <stdio.h>

struct expr_node
{
	char name;
	bool op;	// operator
	expr_node *left, *right;
};

char postfix_expr[10000];
char rlevel_expr[10000];
expr_node node_set[10000];
expr_node* node_stack[10000];
int top;
expr_node* node_queue[10000];
int front, back;

inline void push(expr_node *node)
{
	node_stack[top++] = node;
}

inline expr_node *pop()
{
	return node_stack[--top];
}

inline void enqueue(expr_node *node)
{
	node_queue[back++] = node;
}

inline expr_node *dequeue()
{
	return node_queue[front++];
}

inline bool empty_queue()
{
	return front == back;
}

int main()
{
	int i, tc, len;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s", postfix_expr);
		// parse postfix expression
		top = len = 0;
		for(i = 0; postfix_expr[i] != '\0'; i++)
		{
			node_set[i].name = postfix_expr[i];
			if(postfix_expr[i] >= 'a' && postfix_expr[i] <= 'z')
			{
				node_set[i].op = false;
				node_set[i].left = node_set[i].right = 0;
			}
			else
			{
				node_set[i].op = true;
				node_set[i].right = pop();
				node_set[i].left = pop();
			}
			push(&node_set[i]);
			len++;
		}
		// level-order traversal
		expr_node *ptr;
		front = back = 0;
		enqueue(node_stack[0]);
		i = len-1;
		while(!empty_queue())
		{
			ptr = dequeue();
			rlevel_expr[i--] = ptr->name;
			if(ptr->op)
			{
				enqueue(ptr->left);
				enqueue(ptr->right);
			}
		}
		rlevel_expr[len] = '\0';
		printf("%s\n", rlevel_expr);
	}
	return 0;
}