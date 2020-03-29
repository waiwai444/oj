
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 60013
#define MAX_LEN 16

struct HashMapNode
{
	char word[20];
	size_t word_len;
	size_t step;
	struct HashMapNode* next;
};

struct HashMapHead
{
	size_t size;
	struct HashMapNode* list;
};

struct HashMap
{
	struct HashMapHead vec[HASH_SIZE];
	size_t size;
};

size_t hash(char* word)	// BKDRHash
{
	unsigned int seed = 13131;
	unsigned int hash = 0;
	while(*word)
	{
		hash = hash * seed + (*word++);
	}
	return (hash & 0x7fffffff);
}

struct HashMap hash_map;

struct HashMapNode* hash_insert(char* word)
{
	size_t hv;
	struct HashMapNode *pnode, *qnode = NULL;
	hv = hash(word) % HASH_SIZE;
	pnode = hash_map.vec[hv].list;
	while(pnode != NULL)
	{
		qnode = pnode;
		pnode = pnode->next;
	}
	pnode = (struct HashMapNode*)malloc(sizeof(struct HashMapNode));
	if(qnode == NULL)
		hash_map.vec[hv].list = pnode;
	else
		qnode->next = pnode;
	strcpy(pnode->word, word);
	pnode->word_len = strlen(word);
	pnode->step = 1;
	pnode->next = NULL;
	++hash_map.size;
	return pnode;
}

struct HashMapNode* hash_find(char* word)
{
	size_t hv;
	struct HashMapNode* pnode;
	hv = hash(word) % HASH_SIZE;
	pnode = hash_map.vec[hv].list;
	while(pnode != NULL)
	{
		if(strcmp(pnode->word, word) == 0)
		{
			return pnode;
		}
		pnode = pnode->next;
	}
	return NULL;
}

void update_step(char* adj_word, struct HashMapNode* pnode)
{
	struct HashMapNode* qnode;
	if((qnode = hash_find(adj_word)) != NULL)
	{
		if(qnode->step >= pnode->step)
			pnode->step = qnode->step + 1;
	}
}

int main()
{
	unsigned int i;
	size_t max_step = 1;
	char word[20];
	char temp[20];
	struct HashMapNode* pnode;
	while(scanf("%s", word) != EOF)
	{
		pnode = hash_insert(word);
		pnode->step = 1;
		if(hash_map.size > 1)
		{
			for(i = 0; i < pnode->word_len; i++)
			{
				// same length
				strcpy(temp, word);
				while(--temp[i] >= 'a')
				{
					update_step(temp, pnode);
					if(pnode->step > max_step)
						goto out;
				}
				// length + 1
				if(pnode->word_len < MAX_LEN)
				{
					strncpy(temp, word, i);
					temp[i] = 'z' + 1;
					strcpy(temp + i + 1, word + i);
					while(--temp[i] >= 'a')
					{
						update_step(temp, pnode);
						if(pnode->step > max_step)
							goto out;
					}
				}
				// length - 1
				if(pnode->word_len > 1)
				{
					strncpy(temp, word, i);
					strcpy(temp + i, word + i + 1);
					update_step(temp, pnode);
					if(pnode->step > max_step)
						break;
				}
			}
			// last addition
			if(pnode->word_len < MAX_LEN)
			{
				strcpy(temp, word);
				temp[i] = 'z' + 1;
				while(--temp[i] >= 'a')
				{
					update_step(temp, pnode);
					if(pnode->step > max_step)
						goto out;
				}
			}
out:
			if(pnode->step > max_step)
				max_step = pnode->step;
		}
	}
	printf("%d\n", max_step);
	return 0;
}
