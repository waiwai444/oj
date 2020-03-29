#include <cstdio>
#include <cstring>
#include <list>

#define L 'L'
#define R 'R'
#define U 'U'
#define D 'D'

int n;
std::list<char> cr;
char pic[300][300];

void fold()
{
	bool r = true;
	std::list<char>::iterator it;
	for(it = cr.begin(); it != cr.end(); ++it)
	{
		cr.insert(it, r ? L : R);
		r = !r;
	}
	cr.insert(it, r ? L : R);
}

char next_dir(char d, char t)
{
	if(d == L)
		return t == L ? D : U;
	if(d == R)
		return t == L ? U : D;
	if(d == U)
		return t == L ? L : R;
	return t == L ? R : L;
}

int next_row(int r, char d, char t)
{
	if(d == L)
		return t == L ? r+1 : r;
	if(d == R)
		return t == L ? r : r+1;
	if(d == U)
		return r-1;
	return r;
}

int next_col(int c, char d, char t)
{
	if(d == L)
		return c-1;
	if(d == R)
		return c+1;
	if(d == U)
		return t == L ? c-1 : c+1;
	return t == L ? c+1 : c-1;
}

void draw()
{
	int i, j, left, right, top, bot;
	char dir = R;
	std::list<char>::iterator it;
	left = top = bot = right = 0;
	i = 0, j = 0;
	for(it = cr.begin(); it != cr.end(); ++it)
	{
		i = next_row(i, dir, *it);
		j = next_col(j, dir, *it);
		dir = next_dir(dir, *it);
		if(i < top)
			top = i;
		if(j < left)
			left = j;
		if(i > bot)
			bot = i;
		if(j > right)
			right = j;
	}
	memset(pic, ' ', sizeof(pic));
	i = -top, j = -left;
	bot += -top, right += -left, left = top = 0;
	dir = R;
	pic[i][j] = '_';
	for(it = cr.begin(); it != cr.end(); ++it)
	{
		i = next_row(i, dir, *it);
		j = next_col(j, dir, *it);
		dir = next_dir(dir, *it);
		pic[i][j] = (dir == L || dir == R) ? '_' : '|';
	}
	for(i = 0; i <= bot; i++)
	{
		for(j = right; j >= 0 && pic[i][j] == ' '; j--);
		pic[i][j+1] = 0;
		puts(pic[i]);
	}
	puts("^");
}

void solve()
{
	cr.clear();
	for(int i = 1; i <= n; i++)
		fold();
	draw();
}

int main()
{
	while(scanf("%d", &n), n)
		solve();
	return 0;
}

