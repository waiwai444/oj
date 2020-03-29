#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct TrieNode
{
	bool word;
	TrieNode* link[26];

	TrieNode();
};

TrieNode::TrieNode()
{
	word = false;
	for(int i = 0; i < 26; i++)
		link[i] = NULL;
}

void insert_word(TrieNode* tree, char* word)
{
	int i = 0;
	while(word[i] != '\0')
	{
		if(tree->link[word[i]-'a'] == NULL)
			tree->link[word[i]-'a'] = new TrieNode;
		tree = tree->link[word[i]-'a'];
		i++;
	}
	tree->word = true;
}

void destroy_tree(TrieNode* tree)
{
	int i;
	for(i = 0; i < 26; i++)
		if(tree->link[i] != NULL)
		{
			destroy_tree(tree->link[i]);
			delete tree->link[i];
			tree->link[i] = NULL;
		}
	tree->word = false;
}

bool keyword_match(const TrieNode* tree, char* word)
{
	int i = 0;
	char tmp;
	while(word[i] != '\0')
	{
		tmp = tolower(word[i]);
		if(tree->link[tmp-'a'] == NULL)
			return false;
		tree = tree->link[tmp-'a'];
		i++;
	}
	return tree->word;
}

TrieNode trie_tree;

char excuse_set[20][71];
int key_count[20];

char* split_word(char* str)
{
	static char* ptr = NULL;
	if(str != NULL)
		ptr = str;
	while(*ptr != '\0' && !isalpha(*ptr))
		ptr++;
	if(*ptr == '\0')
		return NULL;
	char* tmp = ptr;
	while(*ptr != '\0' && isalpha(*ptr))
		ptr++;
	if(*ptr != '\0')
		*ptr++ = '\0';
	return tmp;
}

int main()
{
	int i, k, e, max, tc = 0;
	char keyword[21], excuse[75], *tmp;
	while(scanf("%d%d", &k, &e) != EOF)
	{
		while(k--)
		{
			scanf("%s", keyword);
			insert_word(&trie_tree, keyword);
		}

		fgets(excuse, sizeof(excuse), stdin);
		max = 0;
		for(i = 0; i < e; i++)
		{
			fgets(excuse, sizeof(excuse), stdin);
			excuse[strlen(excuse)-1] = 0;
			strcpy(excuse_set[i], excuse);
			key_count[i] = 0;

			tmp = split_word(excuse);
			if(tmp && keyword_match(&trie_tree, tmp))
				key_count[i]++;
			while((tmp = split_word(NULL)) != NULL)
				if(keyword_match(&trie_tree, tmp))
					key_count[i]++;
			if(key_count[i] > max)
				max = key_count[i];
		}

		printf("Excuse Set #%d\n", ++tc);
		for(i = 0; i < e; i++)
			if(key_count[i] == max)
				printf("%s\n", excuse_set[i]);
		printf("\n");

		destroy_tree(&trie_tree);
	}
	return 0;
}
