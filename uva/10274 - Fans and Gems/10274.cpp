#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
#include <string>

struct GameMap
{
	char c[12][25];
	int gem_num;
};

int height, width;
std::set<GameMap> map_set;

bool operator<(const GameMap &m1, const GameMap &m2)
{
	return memcmp(&m1, &m2, sizeof(GameMap)) < 0;
}

int check_gem(const GameMap &gm)
{
	int i, j, r = 0;
	for(i = 1; i < height-1; i++)
		for(j = 1; j < width-1; j++)
			if(gm.c[i][j] >= '1' && gm.c[i][j] <= '3')
				r++;
	return r;
}

int recur_elim(GameMap &gm, int row, int col)
{
	char ch = gm.c[row][col];
	int ret = 1;
	gm.c[row][col] = ' ';
	if(gm.c[row-1][col] == ch)
		ret += recur_elim(gm, row-1, col);
	if(gm.c[row][col+1] == ch)
		ret += recur_elim(gm, row, col+1);
	if(gm.c[row+1][col] == ch)
		ret += recur_elim(gm, row+1, col);
	if(gm.c[row][col-1] == ch)
		ret += recur_elim(gm, row, col-1);
	return ret;
}

int eliminate(GameMap &gm)
{
    int i, j, ret = 0;
	char ch;
	for(i = 1; i < height-1; i++)
	{
		for(j = 1; j < width-1; j++)
		{
			ch = gm.c[i][j];
			if(gm.c[i][j] >= '1' && gm.c[i][j] <= '3' && (gm.c[i-1][j] == ch || gm.c[i][j+1] == ch || gm.c[i+1][j] == ch || gm.c[i][j-1] == ch))
				ret += recur_elim(gm, i, j);
		}
	}
	return ret;
}

bool move_down(GameMap &gm)
{
	int i, j, k;
	bool flag = false;
	for(j = 1; j < width-1; j++)
	{
		i = height-2;
		while(i > 0 && gm.c[i][j] != ' ') i--;
		k = i--;
		while(i > 0)
		{
			while(i > 0 && gm.c[i][j] == ' ') i--;
			if(i <= 0) break;
			if(gm.c[i][j] != '#')
			{
				gm.c[k--][j] = gm.c[i][j];
				gm.c[i--][j] = ' ';
				if(!flag) flag = true;
			}
			else
			{
				while(i > 0 && gm.c[i][j] != ' ') i--;
				k = i--;
			}
		}
	}
	return flag;
}

bool move_left(GameMap &gm)
{
	int i, j, k;
	bool flag = false;
	for(i = 1; i < height-1; i++)
	{
		j = 1;
		while(j < width-1 && gm.c[i][j] != ' ') j++;
		k = j++;
		while(j < width-1)
		{
			while(j < width-1 && gm.c[i][j] == ' ') j++;
			if(j >= width-1) break;
			if(gm.c[i][j] != '#')
			{
				gm.c[i][k++] = gm.c[i][j];
				gm.c[i][j++] = ' ';
				if(!flag) flag = true;
			}
			else
			{
				while(j < width-1 && gm.c[i][j] != ' ') j++;
				k = j++;
			}
		}
	}
	return flag;
}

bool move_right(GameMap &gm)
{
	int i, j, k;
	bool flag = false;
	for(i = 1; i < height-1; i++)
	{
		j = width-2;
		while(j > 0 && gm.c[i][j] != ' ') j--;
		k = j--;
		while(j > 0)
		{
			while(j > 0 && gm.c[i][j] == ' ') j--;
			if(j <= 0) break;
			if(gm.c[i][j] != '#')
			{
				gm.c[i][k--] = gm.c[i][j];
				gm.c[i][j--] = ' ';
				if(!flag) flag = true;
			}
			else
			{
				while(j > 0 && gm.c[i][j] != ' ') j--;
				k = j--;
			}
		}
	}
	return flag;
}

bool move_up(GameMap &gm)
{
	int i, j, k;
	bool flag = false;
	for(j = 1; j < width-1; j++)
	{
		i = 1;
		while(i < height-1 && gm.c[i][j] != ' ') i++;
		k = i++;
		while(i < height-1)
		{
			while(i < height-1 && gm.c[i][j] == ' ') i++;
			if(i >= height-1) break;
			if(gm.c[i][j] != '#')
			{
				gm.c[k++][j] = gm.c[i][j];
				gm.c[i++][j] = ' ';
				if(!flag) flag = true;
			}
			else
			{
				while(i < height-1 && gm.c[i][j] != ' ') i++;
				k = i++;
			}
		}
	}
	return flag;
}

bool (*move_func[4])(GameMap &) = { move_down, move_left, move_right, move_up };
char dir_ch[4] = { 'D', 'L', 'R', 'U' };

void move(GameMap &gm, int dir)
{
	int el = 0;
	bool (*mf)(GameMap &) = move_func[dir];
	while(true)
	{
		if(!mf(gm)) break;
		el += eliminate(gm);
	}
	gm.gem_num -= el;
}

void bfs(GameMap gm)
{
	int i;
	GameMap gm2;
	std::string steps;
	std::queue<GameMap> m_q;
	std::queue<std::string> s_q;
	map_set.clear();
	m_q.push(gm);
	s_q.push(steps);
	map_set.insert(gm);
	while(!m_q.empty())
	{
		gm = m_q.front();
		m_q.pop();
		steps = s_q.front();
		s_q.pop();
        for(i = 0; i < 4; i++)
		{
			gm2 = gm;
			move(gm2, i);
			if(map_set.insert(gm2).second == false) continue;
			steps.append(1, dir_ch[i]);
			if(gm2.gem_num == 0)
			{
				printf("%s\n", steps.c_str());
				return;
			}
			if(steps.size() < 18)
			{
				m_q.push(gm2);
				s_q.push(steps);
			}
			steps.erase(steps.size()-1);
		}
	}
	printf("-1\n");
}

int main()
{
	int i, t;
	GameMap gm;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &height, &width);
		fgets(gm.c[0], sizeof(gm.c[0]), stdin);
		gm.c[0][strlen(gm.c[0])-1] = 0;
		for(i = 0; i < height; i++)
		{
			fgets(gm.c[i], sizeof(gm.c[i]), stdin);
			gm.c[i][strlen(gm.c[i])-1] = 0;
		}
		gm.gem_num = check_gem(gm);
		bfs(gm);
		fgets(gm.c[0], sizeof(gm.c[0]), stdin);
	}
	return 0;
}
