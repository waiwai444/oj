#include <stdio.h>
#include <string.h>

#define DOT_BEGIN 0
#define BAM_BEGIN 9
#define CRAK_BEGIN 18
#define OTHER_BEGIN 27

const char TILE_NAME[34][8] = { "1T", "2T", "3T", "4T", "5T", "6T", "7T", "8T", "9T", 
	"1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", 
	"1W", "2W", "3W", "4W", "5W", "6W", "7W", "8W", "9W", 
	"DONG", "NAN", "XI", "BEI", "ZHONG", "FA", "BAI" };

struct Hand
{
	char tile[34];
};

void add_tile(Hand &hand, char input[])
{
	if(input[1] == 'T')
		hand.tile[DOT_BEGIN+input[0]-'1']++;
	else if(input[1] == 'S')
		hand.tile[BAM_BEGIN+input[0]-'1']++;
	else if(input[1] == 'W')
		hand.tile[CRAK_BEGIN+input[0]-'1']++;
	else if(input[0] == 'D')
		hand.tile[27]++;
	else if(input[0] == 'N')
		hand.tile[28]++;
	else if(input[0] == 'X')
		hand.tile[29]++;
	else if(input[0] == 'B' && input[1] == 'E')
		hand.tile[30]++;
	else if(input[0] == 'Z')
		hand.tile[31]++;
	else if(input[0] == 'F')
		hand.tile[32]++;
	else
		hand.tile[33]++;
}

bool dfs(Hand &hand, int cur, bool has_eye)
{
	bool ret;
	int next;
	if(cur >= 34)
		return has_eye;
	if(hand.tile[cur] == 0)
		return dfs(hand, cur+1, has_eye);
	// pong
	if(hand.tile[cur] >= 3)
	{
		hand.tile[cur] -= 3;
		next = hand.tile[cur] > 0 ? cur : cur+1;
		ret = dfs(hand, next, has_eye);
		hand.tile[cur] += 3;
		if(ret) return true;
	}
	// chow
	if(cur < BAM_BEGIN-2 || cur >= BAM_BEGIN && cur < CRAK_BEGIN-2 || cur >= CRAK_BEGIN && cur < OTHER_BEGIN-2)
	{
		if(hand.tile[cur+1] > 0 && hand.tile[cur+2] > 0)
		{
			hand.tile[cur]--;
			hand.tile[cur+1]--;
			hand.tile[cur+2]--;
			next = hand.tile[cur] > 0 ? cur : cur+1;
			ret = dfs(hand, next, has_eye);
			hand.tile[cur]++;
			hand.tile[cur+1]++;
			hand.tile[cur+2]++;
			if(ret) return true;
		}
	}
	// eye
	if(!has_eye && hand.tile[cur] >= 2)
	{
		hand.tile[cur] -= 2;
		next = hand.tile[cur] > 0 ? cur : cur+1;
		ret = dfs(hand, next, true);
		hand.tile[cur] += 2;
		if(ret) return true;
	}
	return false;
}

void solve(Hand &hand)
{
	bool ready = false;
	for(int i = 0; i < 34; i++)
	{
		if(i < OTHER_BEGIN && hand.tile[i] < 4 || i >= OTHER_BEGIN && hand.tile[i] > 0 && hand.tile[i] < 3)
		{
			hand.tile[i]++;
			if(dfs(hand, 0, false))
			{
				printf(" %s", TILE_NAME[i]);
				if(!ready) ready = true;
			}
			hand.tile[i]--;
		}
	}
	if(!ready) printf(" Not ready\n");
	else printf("\n");
}

int main()
{
	int i, tc = 0;
	char input[8];
	Hand hand;
	while(scanf("%s", input), input[0] != '0')
	{
		memset(&hand, 0, sizeof(Hand));
		add_tile(hand, input);
		for(i = 1; i < 13; i++)
		{
			scanf("%s", input);
			add_tile(hand, input);
		}
		printf("Case %d:", ++tc);
		solve(hand);
	}
	return 0;
}
