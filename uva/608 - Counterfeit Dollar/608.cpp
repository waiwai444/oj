#include <stdio.h>
#include <string.h>

#define UNKNOWN 0
#define NORMAL 1
#define LIGHT 2
#define HEAVY 3

int main()
{
	int i, r, tc;
	char left[8], right[8], weigh[5];
	int coin_status[12];
	bool flag[12];
	scanf("%d", &tc);
	while(tc--)
	{
		memset(coin_status, UNKNOWN, sizeof(coin_status));		
		for(r = 0; r < 3; r++)
		{
			memset(flag, false, sizeof(flag));
			scanf("%s%s%s", left, right, weigh);
			if(weigh[0] == 'e')
			{
				i = 0;
				while(left[i] != '\0')
				{
					coin_status[left[i]-'A'] = NORMAL;
					i++;
				}
				i = 0;
				while(right[i] != '\0')
				{
					coin_status[right[i]-'A'] = NORMAL;
					i++;
				}
			}
			else if(weigh[0] == 'u')
			{
				i = 0;
				while(left[i] != '\0')
				{
					flag[left[i]-'A'] = true;
					if(coin_status[left[i]-'A'] == UNKNOWN)
						coin_status[left[i]-'A'] = HEAVY;
					else if(coin_status[left[i]-'A'] == LIGHT)
						coin_status[left[i]-'A'] = NORMAL;
					i++;
				}
				i = 0;
				while(right[i] != '\0')
				{
					flag[right[i]-'A'] = true;
					if(coin_status[right[i]-'A'] == UNKNOWN)
						coin_status[right[i]-'A'] = LIGHT;
					else if(coin_status[right[i]-'A'] == HEAVY)
						coin_status[right[i]-'A'] = NORMAL;
					i++;
				}
				for(i = 0; i < 12; i++)
					if(!flag[i])
						coin_status[i] = NORMAL;
			}
			else
			{
				i = 0;
				while(left[i] != '\0')
				{
					flag[left[i]-'A'] = true;
					if(coin_status[left[i]-'A'] == UNKNOWN)
						coin_status[left[i]-'A'] = LIGHT;
					else if(coin_status[left[i]-'A'] == HEAVY)
						coin_status[left[i]-'A'] = NORMAL;
					i++;
				}
				i = 0;
				while(right[i] != '\0')
				{
					flag[right[i]-'A'] = true;
					if(coin_status[right[i]-'A'] == UNKNOWN)
						coin_status[right[i]-'A'] = HEAVY;
					else if(coin_status[right[i]-'A'] == LIGHT)
						coin_status[right[i]-'A'] = NORMAL;
					i++;
				}
				for(i = 0; i < 12; i++)
					if(!flag[i])
						coin_status[i] = NORMAL;
			}
		}
		for(i = 0; i < 12; i++)
			if(coin_status[i] == HEAVY)
			{
				printf("%c is the counterfeit coin and it is heavy.\n", 'A'+i);
				break;
			}
			else if(coin_status[i] == LIGHT)
			{
				printf("%c is the counterfeit coin and it is light.\n", 'A'+i);
				break;
			}
	}
	return 0;
}
