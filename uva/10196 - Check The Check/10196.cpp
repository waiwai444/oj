#include <iostream>

using namespace std;

char board[8][8];

bool check(char side, int king_r, int king_c)
{
	int i;
	char temp;
	char offset;
	if(side==0)
		offset = 32;	// white
	else
		offset = 0;	// black

	// upper direction
	for(i=king_r-1; i>=0; i--)
	{
		if((temp=board[i][king_c])!='.')
		{
			if(temp=='R'+offset || temp=='Q'+offset)
				return true;
			break;
		}
	}
	// upper left direction
	if(king_r>0 && king_c>0 && (temp=board[king_r-1][king_c-1])!='.')
	{
		if(side==0 && temp=='p' || temp=='B'+offset || temp=='Q'+offset)
			return true;
	}
	else
	{
		i = 2;
		while(king_r-i>=0 && king_c-i>=0)
		{
			if((temp=board[king_r-i][king_c-i])!='.')
			{
				if(temp=='B'+offset || temp=='Q'+offset)
					return true;
				break;
			}
			i++;
		}
	}
	// upper right direction
	if(king_r>0 && king_c<7 && (temp=board[king_r-1][king_c+1])!='.')
	{
		if(side==0 && temp=='p' || temp=='B'+offset || temp=='Q'+offset)
			return true;
	}
	else
	{
		i = 2;
		while(king_r-i>=0 && king_c+i<=7)
		{
			if((temp=board[king_r-i][king_c+i])!='.')
			{
				if(temp=='B'+offset || temp=='Q'+offset)
					return true;
				break;
			}
			i++;
		}
	}
	// left direction
	for(i=king_c-1; i>=0; i--)
	{
		if((temp=board[king_r][i])!='.')
		{
			if(temp=='R'+offset || temp=='Q'+offset)
				return true;
			break;
		}
	}
	// right direction
	for(i=king_c+1; i<=7; i++)
	{
		if((temp=board[king_r][i])!='.')
		{
			if(temp=='R'+offset || temp=='Q'+offset)
				return true;
			break;
		}
	}
	// lower direction
	for(i=king_r+1; i<=7; i++)
	{
		if((temp=board[i][king_c])!='.')
		{
			if(temp=='R'+offset || temp=='Q'+offset)
				return true;
			break;
		}
	}
	// lower left direction
	if(king_r<7 && king_c>0 && (temp=board[king_r+1][king_c-1])!='.')
	{
		if(side!=0 && temp=='P' || temp=='B'+offset || temp=='Q'+offset)
			return true;
	}
	else
	{
		i = 2;
		while(king_r+i<=7 && king_c-i>=0)
		{
			if((temp=board[king_r+i][king_c-i])!='.')
			{
				if(temp=='B'+offset || temp=='Q'+offset)
					return true;
				break;
			}
			i++;
		}
	}
	// lower right direction
	if(king_r<7 && king_c<7 && (temp=board[king_r+1][king_c+1])!='.')
	{
		if(side!=0 && temp=='P' || temp=='B'+offset || temp=='Q'+offset)
			return true;
	}
	else
	{
		i = 2;
		while(king_r+i<7 && king_c+i<7)
		{
			if((temp=board[king_r+i][king_c+i])!='.')
			{
				if(temp=='B'+offset || temp=='Q'+offset)
					return true;
				break;
			}
			i++;
		}
	}
	// knight
	if(king_r-1>=0)
	{
		if(king_c-2>=0 && board[king_r-1][king_c-2]=='N'+offset)
			return true;
		if(king_c+2<=7 && board[king_r-1][king_c+2]=='N'+offset)
			return true;
	}
	if(king_r-2>=0)
	{
		if(king_c-1>=0 && board[king_r-2][king_c-1]=='N'+offset)
			return true;
		if(king_c+1<=7 && board[king_r-2][king_c+1]=='N'+offset)
			return true;
	}
	if(king_r+1<=7)
	{
		if(king_c-2>=0 && board[king_r+1][king_c-2]=='N'+offset)
			return true;
		if(king_c+2<=7 && board[king_r+1][king_c+2]=='N'+offset)
			return true;
	}
	if(king_r+2<=7)
	{
		if(king_c-1>=0 && board[king_r+2][king_c-1]=='N'+offset)
			return true;
		if(king_c+1<=7 && board[king_r+2][king_c+1]=='N'+offset)
			return true;
	}
	return false;
}

int main()
{
	int i, j, d;
	int whiteKing_r, whiteKing_c, blackKing_r, blackKing_c;
	char line[10];
	bool stop;
	d = 1;
	while(true)
	{
		stop = true;
		whiteKing_r = whiteKing_c = blackKing_r = blackKing_c = -1;
		for(i=0; i<8; i++)
		{
			cin.getline(line, 10);
			for(j=0; j<8; j++)
			{
				board[i][j] = line[j];
				if(line[j]!='.')
					stop = false;
				if(line[j]=='k')
				{
					blackKing_r = i;
					blackKing_c = j;
				}
				else if(line[j]=='K')
				{
					whiteKing_r = i;
					whiteKing_c = j;
				}
			}
		}
		if(stop)
			break;
		cin.getline(line, 10);
		if(whiteKing_r!=-1 && check(0, whiteKing_r, whiteKing_c))
			cout<<"Game #"<<d<<": white king is in check."<<endl;
		else if(blackKing_r!=-1 && check(1, blackKing_r, blackKing_c))
			cout<<"Game #"<<d<<": black king is in check."<<endl;
		else
			cout<<"Game #"<<d<<": no king is in check."<<endl;
		d++;
	}
	return 0;
}
