#include <stdio.h>
#include <string>
#include <vector>

#define HASH_SIZE 130003

int word_num;
std::string dict[120000];
std::vector<int> hash_table[HASH_SIZE];

unsigned int BKDRhash(const char *word)
{
	unsigned int seed = 131, hash = 0;
	while(*word)
		hash = hash*seed+*word++;
	return hash&0x7fffffff;
}

int main()
{
	char word[100];
	unsigned int hash;
	std::string sub;
	word_num = 0;
	while(scanf("%s", word) != EOF)
	{
		dict[word_num] = word;
		hash = BKDRhash(word)%HASH_SIZE;
		hash_table[hash].push_back(word_num);
		word_num++;
	}
	for(int i = 1; i < word_num; i++)
	{
		for(int j = 1; j < dict[i].size(); j++)
		{
			sub = dict[i].substr(0, j);
			hash = BKDRhash(sub.c_str())%HASH_SIZE;
			bool found = false;
			for(int k = 0; k < hash_table[hash].size(); k++)
				if(dict[hash_table[hash][k]] == sub)
				{
					found = true;
					break;
				}
			if(!found)
				continue;
			sub = dict[i].substr(j);
			hash = BKDRhash(sub.c_str())%HASH_SIZE;
			found = false;
			for(int k = 0; k < hash_table[hash].size(); k++)
				if(dict[hash_table[hash][k]] == sub)
				{
					found = true;
					break;
				}
			if(found)
			{
				printf("%s\n", dict[i].c_str());
				break;
			}
		}
	}
	return 0;
}
