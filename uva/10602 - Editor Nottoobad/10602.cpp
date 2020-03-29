#include <stdio.h>
#include <string.h>

struct TrieNode
{
	TrieNode *child[26];
	int wcount;
	TrieNode() : wcount(0) { memset(child, NULL, sizeof(child)); }
};

TrieNode trie_tree;
int edge_num;
char first_word[101];

void clear_tree(TrieNode *node)
{
	for(int i = 0; i < 26; i++)
		if(node->child[i])
		{
			clear_tree(node->child[i]);
			delete node->child[i];
			node->child[i] = NULL;
			edge_num--;
		}
	node->wcount = 0;
}

void insert_word(TrieNode *node, char *word, int begin)
{
	char ch = word[begin];
	if(ch == '\0')
		node->wcount++;
	else
	{
		ch -= 'a';
		if(node->child[ch] == NULL)
		{
			node->child[ch] = new TrieNode;
			edge_num++;
		}
		insert_word(node->child[ch], word, begin+1);
	}
}

void traverse_tree(TrieNode *node, char *cur_word, int depth, bool first_path)
{
	int i;
	if(first_path && first_word[depth] != '\0')
	{
		char ch = first_word[depth];
		cur_word[depth] = ch;
		ch -= 'a';
		traverse_tree(node->child[ch], cur_word, depth+1, true);
		
		if(node->wcount)
		{
			cur_word[depth] = '\0';
			for(i = node->wcount; i > 0; --i)
				printf("%s\n", cur_word);
		}
		
		for(i = 0; i < 26; i++)
			if(node->child[i] && i != ch)
			{
				cur_word[depth] = i+'a';
				traverse_tree(node->child[i], cur_word, depth+1, false);
			}
	}
	else
	{
		if(node->wcount)
		{
			cur_word[depth] = '\0';
			for(i = node->wcount; i > 0; --i)
				printf("%s\n", cur_word);
		}
		for(i = 0; i < 26; i++)
			if(node->child[i])
			{
				cur_word[depth] = i+'a';
				traverse_tree(node->child[i], cur_word, depth+1, false);
			}
	}
}

int main()
{
	int tc, n;
	char cur_word[101];
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%s", &n, first_word);
		insert_word(&trie_tree, first_word, 0);
		while(--n)
		{
			scanf("%s", cur_word);
			insert_word(&trie_tree, cur_word, 0);
		}
		printf("%d\n", edge_num);
		traverse_tree(&trie_tree, cur_word, 0, true);
		clear_tree(&trie_tree);
	}
	return 0;
}