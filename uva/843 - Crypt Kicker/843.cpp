#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#define MAXDICT 1000

using namespace std;

vector<string> dictionary;	// the dictionary
map<string, vector<int> > cipherset;	// store the cipher texts and their indices of corresponding candidate plain texts
map<string, vector<int> >::iterator iter;

char wordstruct[MAXDICT][20];	// record the structures of the plain words (i.e. repetition)

// get the structure of the word, that is, the repetition of characters in a word
char *getWordStruct(string str)
{
	int i, k, l, t;
	char charLabel[26];
	for(i=0; i<26; i++)
		charLabel[i] = 0;
	l = strlen(str.c_str());
	t = 1;
	char *s = new char[20];
	for(i=0; i<l; i++)
	{
		k = str[i]-'a';
		if(charLabel[k]==0)
		{
			charLabel[k] = t;
			s[i] = t;
			t++;
		}
		else
		{
			s[i] = charLabel[k];
		}
	}
	s[i] = 0;
	return s;
}

void getAllPlainWordStructs()
{
	int i;
	char *s;
	for(i=0; i<dictionary.size(); i++)
	{
		s = getWordStruct(dictionary[i]);
		strcpy(wordstruct[i], s);
		delete[] s;
	}
}


// find out candidate plain texts for each cipher text according to the length and the repetition of characters
void classify()
{
	int i, j, k, l, t;
	char *cipherstruct;
	bool same;
	for(iter=cipherset.begin(); iter!=cipherset.end(); iter++)
	{
		l = strlen(iter->first.c_str());
		cipherstruct = getWordStruct(iter->first);
		for(i=0; i<dictionary.size(); i++)
		{
			if(l==strlen(dictionary[i].c_str()))
			{
				same = true;
				for(j=0; j<l; j++)
				{
					if(wordstruct[i][j]!=cipherstruct[j])
					{
						same = false;
						break;
					}
				}
				if(same)
					iter->second.push_back(i);
			}
		}
		delete[] cipherstruct;
	}
}

// main decryption step, by recurrence and backtrace. the iterator is used to iterate the cipher text set by recurrence.
bool decrypt(char restore[], char substit[], const map<string, vector<int> >::iterator &iter, const map<string, vector<int> >::iterator &end)
{
	int i, j, l;
	bool fail = false;
	map<string, vector<int> >::iterator iter2;
	char restore2[26];
	char substit2[26];
	const string *cstr, *pstr;
	cstr = &iter->first;
	l = strlen(cstr->c_str());
	for(i=0; i<iter->second.size(); i++)
	{
		for(j=0; j<26; j++)
		{
			restore2[j] = restore[j];
			substit2[j] = substit[j];
		}
		pstr = &dictionary[iter->second[i]];
		// see if this plain word can be mapped to this cipher word
		for(j=0; j<l; j++)
		{
			if(restore2[cstr->at(j)-'a']!=0 && restore2[cstr->at(j)-'a']!=pstr->at(j))	// the character in the cipher word is already mapped to other plain character
			{
				fail = true;
				break;
			}
			if(substit2[pstr->at(j)-'a']!=0 && substit2[pstr->at(j)-'a']!=cstr->at(j))	// the character in the plain word is already mapped to other cipher character
			{
				fail = true;
				break;
			}
			restore2[cstr->at(j)-'a'] = pstr->at(j);
			substit2[pstr->at(j)-'a'] = cstr->at(j);
		}
		if(fail)
		{
			fail = false;
			continue;
		}
		iter2 = iter;
		iter2++;
		if(iter2==end || decrypt(restore2, substit2, iter2, end))	// go to the next cipher word by recurrence
		{
			for(j=0; j<26; j++)
			{
				restore[j] = restore2[j];
				substit[j] = substit2[j];
			}
			return true;
		}
	}
	return false;
}

int main()
{
	int i, l;
	int n;
	char line[100];
	char temp[100];
	char *cipher;
	cin>>n;
	cin.getline(line, 100);
	dictionary.reserve(MAXDICT);
	for(i=0; i<n; i++)
	{
		cin.getline(line, 20);
		dictionary.push_back(string(line));
	}
	getAllPlainWordStructs();	// get the structures of plain texts
	
	
	char restore[26];	// the current restoration of cipher characters
	char substit[26];	// the current substition of plain characters
	while(cin.getline(line, 100))
	{
		if(line[0]==0)
			break;
		strcpy(temp, line);
		cipher = strtok(temp, " ");
		if(cipher==NULL)
			continue;
		cipherset[string(cipher)] = vector<int>();
		while((cipher = strtok(NULL, " "))!=NULL)
			cipherset[string(cipher)] = vector<int>();
		classify();		// classify cipher texts into different partitions according to their lengths and repitition of characters
		memset(restore, 0, sizeof(restore));
		memset(substit, 0, sizeof(substit));
		l = strlen(line);
		if(decrypt(restore, substit, cipherset.begin(), cipherset.end()))
		{
			for(i=0; i<l; i++)
			{
				if(line[i]==' ')
					cout<<' ';
				else
					cout<<restore[line[i]-'a'];
			}
			cout<<endl;
		}
		else
		{
			for(i=0; i<l; i++)
			{
				if(line[i]==' ')
					cout<<' ';
				else
					cout<<'*';
			}
			cout<<endl;
		}
		cipherset.clear();
	}
	return 0;
}