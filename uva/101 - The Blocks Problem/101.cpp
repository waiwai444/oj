#include <stdio.h>

struct block
{
	int value;
	int pos;
	block *up, *down;
};

block block_set[25];
block *slot_bottom[25];
block *slot_top[25];

void destack(block *base)	// de-stack blocks above *base
{
	block *p = base->up, *q;
	while(p)
	{
		q = p->up;
		p->up = p->down = 0;
		slot_bottom[p->value] = p;
		slot_top[p->value] = p;
		p->pos = p->value;
		p = q;
	}
	base->up = 0;
	slot_top[base->pos] = base;
}

void move(block *p, block *new_base)	// move *p onto *new_base
{
	slot_top[new_base->pos] = slot_top[p->pos];
	slot_top[p->pos] = p->down;
	if(p->down)
		p->down->up = 0;
	else
		slot_bottom[p->value] = 0;
	p->down = new_base;
	new_base->up = p;
	while(p)
	{
		p->pos = new_base->pos;
		p = p->up;
	}
}

void execute(const char *com_type1, int src, const char *com_type2, int dest)
{
	if(src == dest || block_set[src].pos == block_set[dest].pos)
		return;
	if(com_type1[0] == 'm')	// move
	{
		if(com_type2[1] == 'n')	// onto
		{
			// return upper blocks
			destack(&block_set[src]);
			destack(&block_set[dest]);
			// move onto
			move(&block_set[src], &block_set[dest]);
		}
		else	// over
		{
			// return upper blocks on src
			destack(&block_set[src]);
			// move
			move(&block_set[src], slot_top[block_set[dest].pos]);
		}
	}
	else	// pile
	{
		if(com_type2[1] == 'n')	// onto
		{
			// return upper blocks on dest
			destack(&block_set[dest]);
			// move
			move(&block_set[src], &block_set[dest]);
		}
		else	// over
		{
			// move
			move(&block_set[src], slot_top[block_set[dest].pos]);
		}
	}
}

int main()
{
	int i, n;
	char command[20], com_type1[5], com_type2[5];
	int src, dest;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		block_set[i].value = block_set[i].pos = i;
		slot_top[i] = slot_bottom[i] = &block_set[i];		
	}
	fgets(command, 20, stdin);
	while(1)
	{
		fgets(command, 20, stdin);
		if(command[0] == 'q')
			break;
		sscanf(command, "%s%d%s%d", com_type1, &src, com_type2, &dest);
		execute(com_type1, src, com_type2, dest);
	}
	block *p;
	for(i = 0; i < n; i++)
	{
		printf("%d:", i);
		p = slot_bottom[i];
		while(p)
		{
			printf(" %d", p->value);
			p = p->up;
		}
		printf("\n");
	}
	return 0;
}
