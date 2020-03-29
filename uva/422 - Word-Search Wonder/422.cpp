
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// The class for the letter grid
class LetterGrid {
	size_t n;
	char *grid_storage;
	char **letter_grid;
public:
	LetterGrid() : n(0), grid_storage(0), letter_grid(0) {}
	~LetterGrid();
	size_t nsize() { return n; }
	bool read_grid(istream &in);
	void clear();
	char *operator [](size_t index) { return letter_grid[index]; }
};

LetterGrid::~LetterGrid()
{
	if(grid_storage)
		delete[] grid_storage;
	if(letter_grid)
		delete[] letter_grid;
}

bool LetterGrid::read_grid(istream &in)
{
	unsigned int i;
	in>>n;
	grid_storage = new char[n*n];
	for(i=0; i<n*n; i++)
		in>>grid_storage[i];
	letter_grid = new char *[n];
	for(i=0; i<n; i++)
		letter_grid[i] = &grid_storage[i*n];
	return true;
}

void LetterGrid::clear()
{
	if(grid_storage)
		delete[] grid_storage;
	if(letter_grid)
		delete[] letter_grid;
	n = 0;
}

// The class used as a dictionary for all input words.
class TrieTree {
	const static int alpha_size = 26;
	struct Node {
		Node *child[alpha_size];
		bool is_word;
		int id;
		Node() : is_word(false), id(-1) { memset(child, NULL, sizeof(child)); }
	};
	Node root;
	unsigned int _word_num;
	unsigned int _depth;
public:
	TrieTree(const vector<string> &words) : _word_num(0), _depth(0) { construct_tree(words); }
	~TrieTree();
	void construct_tree(const vector<string> &words);
	bool search_by_letter(bool start, char letter, bool &is_word, int &id);	// Search the tree by feeding a single letter each time
	unsigned int word_num() { return _word_num; }
	unsigned int depth() { return _depth; }
};

TrieTree::~TrieTree()
{
	int i;
	Node *cur_node;
	vector<Node *> nodes;
	vector<int> idx;
	nodes.push_back(&root);
	idx.push_back(0);
	while(!nodes.empty())
	{
		cur_node = nodes.back();
		i = idx.back();
		while(i<alpha_size && cur_node->child[i]==NULL) i++;
		if(i>=alpha_size)
		{
			if(cur_node!=&root)
				delete cur_node;
			nodes.pop_back();
			idx.pop_back();
		}
		else
		{
			nodes.push_back(cur_node->child[i]);
			idx.back() = i+1;
			idx.push_back(0);
		}
	}
	nodes.clear();
}

void TrieTree::construct_tree(const vector<string> &words)
{
	size_t i, j;
	Node *cur_node, *tmp_node;
	_word_num = 0;
	_depth = 0;
	for(i=0; i<words.size(); i++)
	{
		cur_node = &root;
		if(words[i].length()>_depth)
			_depth = words[i].length();
		for(j=0; j<words[i].length(); j++)
		{
			tmp_node = cur_node->child[words[i][j]-'A'];
			if(tmp_node==NULL)
			{
				tmp_node = new Node;
				cur_node->child[words[i][j]-'A'] = tmp_node;
			}
			cur_node = tmp_node;
		}
		cur_node->is_word = true;	// A new word has been inserted
		cur_node->id = i;	// Record the id of this word
		_word_num++;
	}
}

bool TrieTree::search_by_letter(bool start, char letter, bool &is_word, int &id)
{
	static Node *cur_node;
	if(start)
		cur_node = &root;
	if(islower(letter))
		letter = toupper(letter);
	if(cur_node==NULL || cur_node->child[letter-'A']==NULL)
		return false;	// No this branch in the tree
	cur_node = cur_node->child[letter-'A'];
	is_word = cur_node->is_word;
	id = cur_node->id;
	return true;
}

// Input all words
inline vector<string> read_words(istream &in)
{
	vector<string> words;
	string word;
	words.reserve(100);
	while(in>>word && word[0]!='0')
		words.push_back(word);	// All words are guaranteed to be in uppercase
	return words;
}

// Used to record the position of the occurrence of a word
struct WordPosition {
	int r1, c1, r2, c2;
};

inline void print_word_position(vector<WordPosition> &pos)
{
	unsigned int i;
	for(i=0; i<pos.size(); i++)
	{
		if(pos[i].r1==-1)
			cout<<"Not found"<<endl;
		else
			cout<<pos[i].r1+1<<','<<pos[i].c1+1<<' '<<pos[i].r2+1<<','<<pos[i].c2+1<<endl;
	}
}

inline void find_words_direct(vector<WordPosition> &pos, LetterGrid &letter_grid, TrieTree &dict, int beg_row, int beg_col, int row_dir, int col_dir)
{
	unsigned int u, v, k;
	int id;
	bool is_word;
	bool wrapped = false;
	u = beg_row, v = beg_col, k = 1;
	while(k<=dict.depth() && u>=0 && u<letter_grid.nsize() && v>=0 && v<letter_grid.nsize())
	{
		if(!dict.search_by_letter(k==1?true:false, letter_grid[u][v], is_word, id))	// No such a word in the dictionary
			break;
		if(is_word && pos[id].r1==-1)
			pos[id].r1 = beg_row, pos[id].c1 = beg_col, pos[id].r2 = u, pos[id].c2 = v;
		u += row_dir;
		v += col_dir;
		k++;
	}
}

// The main procedure to find each word in the letter grid
void find_words(LetterGrid &letter_grid, TrieTree &dict)
{
	unsigned int i, j;
	bool is_word;
	int id;
	vector<WordPosition> pos(dict.word_num());
	for(i=0; i<dict.word_num(); i++)
		pos[i].r1 = pos[i].c1 = pos[i].r2 = pos[i].c2 = -1;
	for(i=0; i<letter_grid.nsize(); i++)
	{
		for(j=0; j<letter_grid.nsize(); j++)
		{
			if(!dict.search_by_letter(true, letter_grid[i][j], is_word, id))
				continue;
			// top to bottom
			find_words_direct(pos, letter_grid, dict, i, j, 1, 0);
			// bottom to top
			find_words_direct(pos, letter_grid, dict, i, j, -1, 0);
			// left to right
			find_words_direct(pos, letter_grid, dict, i, j, 0, 1);
			// right to left
			find_words_direct(pos, letter_grid, dict, i, j, 0, -1);
			// bottom left to top right
			find_words_direct(pos, letter_grid, dict, i, j, -1, 1);
			// bottom right to top left
			find_words_direct(pos, letter_grid, dict, i, j, -1, -1);
			// top left to bottom right
			find_words_direct(pos, letter_grid, dict, i, j, 1, 1);
			// top right to bottom left
			find_words_direct(pos, letter_grid, dict, i, j, 1, -1);
		}
	}
	print_word_position(pos);
}

int main()
{
	LetterGrid letter_grid;
	letter_grid.read_grid(cin);
	TrieTree dict(read_words(cin));
	find_words(letter_grid, dict);
	return 0;
}