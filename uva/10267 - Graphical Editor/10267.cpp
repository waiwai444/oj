#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

char bitmap[250][250];
int m, n;

int queue[250*250][2];
int head, tail;

void create(char *param)
{
	m = atoi(strtok(param, " "));
	n = atoi(strtok(NULL, " "));
	memset(bitmap, 'O', 250*250*sizeof(char));
}

void paint(char *param)
{
	int x, y;
	x = atoi(strtok(param, " "));
	y = atoi(strtok(NULL, " "));
	bitmap[y-1][x-1] = *strtok(NULL, " ");
}

void vline(char *param)
{
	int i, x, y1, y2;
	int temp;
	char c;
	x = atoi(strtok(param, " "));
	y1 = atoi(strtok(NULL, " "));
	y2 = atoi(strtok(NULL, " "));
	if(y1>y2)
		temp = y1, y1 = y2, y2 = temp;
	c = *strtok(NULL, " ");
	for(i=y1; i<=y2; i++)
	{
		bitmap[i-1][x-1] = c;
	}
}

void hline(char *param)
{
	int i, x1, x2, y;
	int temp;
	char c;
	x1 = atoi(strtok(param, " "));
	x2 = atoi(strtok(NULL, " "));
	y = atoi(strtok(NULL, " "));
	if(x1>x2)
		temp = x1, x1 = x2, x2 = temp;
	c = *strtok(NULL, " ");
	for(i=x1; i<=x2; i++)
	{
		bitmap[y-1][i-1] = c;
	}
}

void rect(char *param)
{
	int i, j, x1, x2, y1, y2;
	int temp;
	char c;
	x1 = atoi(strtok(param, " "));
	y1 = atoi(strtok(NULL, " "));
	x2 = atoi(strtok(NULL, " "));
	y2 = atoi(strtok(NULL, " "));
	if(x1>x2)
		temp = x1, x1 = x2, x2 = temp;
	if(y1>y2)
		temp = y1, y1 = y2, y2 = temp;
	c = *strtok(NULL, " ");
	for(i=x1; i<=x2; i++)
		for(j=y1; j<=y2; j++)
			bitmap[j-1][i-1] = c;
}

void fillRegion(char *param)
{
	int x, y;
	char old, c;
	x = atoi(strtok(param, " "));
	y = atoi(strtok(NULL, " "));
	c = *strtok(NULL, " ");
	old = bitmap[y-1][x-1];
	if(old==c)
		return;
	bitmap[y-1][x-1] = c;
	queue[0][0] = x-1, queue[0][1] = y-1;
	head = 0, tail = 1;
	while(head!=tail)
	{
		x = queue[head][0];
		y = queue[head++][1];
		if(y+1<n && bitmap[y+1][x]==old)
		{
			bitmap[y+1][x] = c;
			queue[tail][0] = x, queue[tail++][1] = y+1;
		}
		if(y-1>=0 && bitmap[y-1][x]==old)
		{
			bitmap[y-1][x] = c;
			queue[tail][0] = x, queue[tail++][1] = y-1;
		}
		if(x+1<m && bitmap[y][x+1]==old)
		{
			bitmap[y][x+1] = c;
			queue[tail][0] = x+1, queue[tail++][1] = y;
		}
		if(x-1>=0 && bitmap[y][x-1]==old)
		{
			bitmap[y][x-1] = c;
			queue[tail][0] = x-1, queue[tail++][1] = y;
		}
	}
}

void output(char *param)
{
	int i, j;
	cout<<param<<endl;
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
			cout<<bitmap[i][j];
		cout<<endl;
	}
}

int main()
{
	char command[1024];
	while(cin.getline(command, 1024))
	{
		if(command[0]=='X')
			break;
		switch(command[0])
		{
		case 'I':
			create(&command[2]);
			break;
		case 'C':
			memset(bitmap, 'O', 250*250*sizeof(char));
			break;
		case 'L':
			paint(&command[2]);
			break;
		case 'V':
			vline(&command[2]);
			break;
		case 'H':
			hline(&command[2]);
			break;
		case 'K':
			rect(&command[2]);
			break;
		case 'F':
			fillRegion(&command[2]);
			break;
		case 'S':
			output(&command[2]);
			break;
		}
	}
	return 0;
}