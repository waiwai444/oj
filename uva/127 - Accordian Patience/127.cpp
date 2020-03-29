#include <stdio.h>

struct card
{
	char suit;
	char rank;
};

struct card_pile
{
	card card_set[52];
	int card_num;
	card_pile *left, *right;
	
	card *top() const { return const_cast<card*>(&card_set[card_num-1]); }
};

struct game_pack
{
	card_pile pile[52];
	int pile_num;
};

inline bool match(const card_pile *pile1, const card_pile *pile2)
{
	card *c1 = pile1->top();
	card *c2 = pile2->top();
	return c1->suit == c2->suit || c1->rank == c2->rank;
}

inline void remove_pile(card_pile *pile)
{
	if(pile->left)
		pile->left->right = pile->right;
	if(pile->right)
		pile->right->left = pile->left;
}

inline void place(card_pile *from, card_pile *to, game_pack *pack)
{
	to->card_set[to->card_num++] = from->card_set[--(from->card_num)];
	if(from->card_num == 0)
	{
		remove_pile(from);
		pack->pile_num--;
	}
}

int main()
{
	int i;
	char input[80];
	game_pack pack;
	while(1)
	{
		fgets(input, 80, stdin);
		if(input[0] == '#')
			break;
		for(i = 0; i < 26; i++)
		{
			card tmp_card = { input[3*i], input[3*i+1] };
			pack.pile[i].card_set[0] = tmp_card;
			pack.pile[i].card_num = 1;
			pack.pile[i].left = (i == 0 ? 0 : &pack.pile[i-1]);
			pack.pile[i].right = &pack.pile[i+1];
		}
		fgets(input, 80, stdin);
		for(i = 0; i < 26; i++)
		{
			card tmp_card = { input[3*i], input[3*i+1] };
			pack.pile[i+26].card_set[0] = tmp_card;
			pack.pile[i+26].card_num = 1;
			pack.pile[i+26].left = &pack.pile[i+25];
			pack.pile[i+26].right = (i == 25 ? 0 : &pack.pile[i+27]);
		}
		pack.pile_num = 52;
		
		card_pile *ptr = &pack.pile[1], *tmp_ptr;
		while(1)
		{
			if(ptr->left && ptr->left->left && (tmp_ptr = ptr->left->left->left) && match(ptr, tmp_ptr))
			{
				place(ptr, tmp_ptr, &pack);
				ptr = &pack.pile[0];
			}
			else if(ptr->left && match(ptr, ptr->left))
			{
				place(ptr, ptr->left, &pack);
				ptr = &pack.pile[0];
			}
			else
			{
				ptr = ptr->right;
				if(ptr == 0)
					break;
			}
		}
		
		if(pack.pile_num > 1)
			printf("%d piles remaining:", pack.pile_num);
		else
			printf("1 pile remaining:");
		ptr = &pack.pile[0];
		while(ptr)
		{
			printf(" %d", ptr->card_num);
			ptr = ptr->right;
		}
		printf("\n");
	}
	return 0;
}
