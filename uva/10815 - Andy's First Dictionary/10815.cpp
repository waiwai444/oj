#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct TrieNode
{
	bool word;
	TrieNode* link[26];

	TrieNode() : word(false) { memset(link, 0, sizeof(link)); }
};

char* insert_word(TrieNode* tree, char* word)
{
	int i = 0;
	char ch;
	TrieNode* ptr = tree;
	while(isalpha(ch = word[i]))
	{
		if(isupper(ch))
			ch += ('a'-'A');
		if(ptr->link[ch-'a'] == 0)
			ptr->link[ch-'a'] = new TrieNode;
		ptr = ptr->link[ch-'a'];
		i++;
	}
	if(!ptr->word)
		ptr->word = true;
	return &word[i];
}

void output_tree(const TrieNode* tree, char *word, int len)
{
	if(tree->word)
	{
		word[len] = '\0';
		printf("%s\n", word);
	}
	for(int i = 0; i < 26; i++)
	{
		if(tree->link[i] != 0)
		{
			word[len] = i+'a';
			output_tree(tree->link[i], word, len+1);
		}
	}
}

int main()
{
	char buf[201];
	char* ptr;
	TrieNode tree;
	while(fgets(buf, sizeof(buf), stdin))
	{
		buf[strlen(buf)-1] = 0;
		ptr = buf;
		while(*ptr != '\0')
		{
			while(*ptr != '\0' && !isalpha(*ptr))
				ptr++;
			if(*ptr != '\0')
				ptr = insert_word(&tree, ptr);
		}
	}
	output_tree(&tree, buf, 0);
	return 0;
}
