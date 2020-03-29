#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <vector>

#define TITLE_LEN 300

struct TrieNode
{
	TrieNode* alpha[26];
	bool has_word;
	void* data;

	TrieNode() : has_word(false), data(0) { memset(alpha, 0, sizeof(alpha)); }
};

struct TrieTree
{
	TrieNode root;

	TrieNode* insert(const char* word)
	{
		int i = 0;
		TrieNode* ptr = &root;
		while(isalpha(word[i]))
		{
			int j = tolower(word[i])-'a';
			if(ptr->alpha[j] == 0)
				ptr->alpha[j] = new TrieNode;
			ptr = ptr->alpha[j];
			i++;
		}
		ptr->has_word = true;
		return ptr;
	}

	bool find(const char* word)
	{
		int i = 0;
		TrieNode* ptr = &root;
		while(isalpha(word[i]))
		{
			int j = tolower(word[i])-'a';
			if(ptr->alpha[j] == 0)
				return false;
			ptr = ptr->alpha[j];
			i++;
		}
		return ptr->has_word;
	}

	void recur_traverse(TrieNode* pnode, void (*func)(void*))
	{
		int i;
		if(pnode->data)
			(*func)(pnode->data);
		for(i = 0; i < 26; i++)
			if(pnode->alpha[i] != 0)
			{
				recur_traverse(pnode->alpha[i], func);
			}
	}

	void traverse(void (*func)(void*))
	{
		recur_traverse(&root, func);
	}
};

struct KeywordInTitle
{
	int title_idx;
	int keyword_idx;
};

TrieTree ignore;
TrieTree keyword;
int title_num;
char titles[201][TITLE_LEN+1];

void insert_keyword(const char* word, int title_idx, int keyword_idx)
{
	if(!ignore.find(word))
	{
		TrieNode* node = keyword.insert(word);
		std::vector<KeywordInTitle> *data = (std::vector<KeywordInTitle> *)node->data;
		if(data == 0)
		{
			data = new std::vector<KeywordInTitle>;
			data->reserve(20);
			node->data = (void*)data;
		}
		KeywordInTitle kit = { title_idx, keyword_idx };
		data->push_back(kit);
	}
}

char output[TITLE_LEN+1];
void print_kwic_item(void* data)
{
	int i;
	std::vector<KeywordInTitle> *kit_vec = (std::vector<KeywordInTitle>*)data;
	for(i = 0; i < kit_vec->size(); i++)
	{
		sprintf(output, "%s", titles[(*kit_vec)[i].title_idx]);
		char *ptr = &output[(*kit_vec)[i].keyword_idx];
		while(*ptr != ' ' && *ptr != '\0')
		{
			*ptr = toupper(*ptr);
			ptr++;
		}
		printf("%s\n", output);
	}
}

int main()
{
	int i, j, k;
	char str[20];
	while(scanf("%s", str))	// get ignores
	{
		if(str[0] == ':')
			break;
		ignore.insert(str);
	}
	fgets(str, sizeof(str), stdin);
	title_num = 0;
	while(fgets(titles[title_num], sizeof(titles[title_num]), stdin))	// get titles and parse keywords
	{
		titles[title_num][strlen(titles[title_num])-1] = 0;
		i = 0;
		bool in_word = false;
		while(titles[title_num][i] != '\0')
		{
			titles[title_num][i] = tolower(titles[title_num][i]);
			if(!in_word && titles[title_num][i] != ' ')
			{
				j = i;
				k = 1;
				in_word = true;
			}
			else if(in_word)
			{
				if(titles[title_num][i] == ' ')
				{
					in_word = false;
					strncpy(str, titles[title_num]+j, k);
					str[k] = '\0';
					insert_keyword(str, title_num, j);					
				}
				else
					k++;
			}
			i++;
		}
		if(in_word)
		{
			strncpy(str, titles[title_num]+j, k);
			str[k] = '\0';
			insert_keyword(str, title_num, j);
		}
		title_num++;
	}

	keyword.traverse(print_kwic_item);
	
	return 0;
}
