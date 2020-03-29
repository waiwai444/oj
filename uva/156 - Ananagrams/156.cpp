#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Word
{
	int len;
	char word[21];
	char alpha[21];
};

struct TrieNode
{
	TrieNode* ch[26];
	int nwords;
	
	TrieNode() : nwords(0) { memset(ch, 0, sizeof(ch)); }
};

struct TrieTree
{
	TrieNode root;
	
	TrieNode* insert(const char* word)
	{
		int i = 0;
		TrieNode* ptr = &root;
		while(word[i] != '\0')
		{
			int ch = tolower(word[i])-'a';
			if(ptr->ch[ch] == 0)
				ptr->ch[ch] = new TrieNode;
			ptr = ptr->ch[ch];
			i++;
		}
		ptr->nwords++;
		return ptr;
	}
};

int nwords;
Word dict[1001];

int cmp_alpha(const void* a, const void* b)
{
	const char *c1 = (const char*)a, *c2 = (const char*)b;
	if(*c1 < *c2)
		return -1;
	else if(*c1 > *c2)
		return 1;
	return 0;
}

int cmp_word(const void* a, const void* b)
{
	const Word *w1 = (const Word*)a, *w2 = (const Word*)b;
	return strcmp(w1->word, w2->word);
}

int main()
{
	int i, j;
	TrieTree dict_tree;
	nwords = 0;
	while(scanf("%s", dict[nwords].word))
	{
		if(dict[nwords].word[0] == '#')
			break;
		else if(dict_tree.insert(dict[nwords].word)->nwords == 1)
			nwords++;
	}
	for(i = 0; i < nwords; i++)
	{
		j = 0;
		while(dict[i].word[j] != '\0')
		{
			dict[i].alpha[j] = tolower(dict[i].word[j]);
			j++;
		}
		dict[i].alpha[j] = '\0';
		dict[i].len = j;
		qsort(dict[i].alpha, j, sizeof(char), cmp_alpha);
	}
	
	qsort(dict, nwords, sizeof(Word), cmp_word);
	TrieTree alpha_tree;
	TrieNode* word_node[1000];
	for(i = 0; i < nwords; i++)
		word_node[i] = alpha_tree.insert(dict[i].alpha);
	for(i = 0; i < nwords; i++)
		if(word_node[i]->nwords == 1)
			printf("%s\n", dict[i].word);
		
	return 0;
}
