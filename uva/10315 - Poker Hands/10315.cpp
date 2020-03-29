#include <iostream>
#include <stdlib.h>

#define BLACKWIN 1
#define WHITEWIN 2
#define TIE 0

using namespace std;

char black[5][2];
char white[5][2];

//char mapValue(char p)
//{
//	if(p>='2' && p<='9') return p-'0';
//	switch(p) {
//		case 'T':
//			return 10;
//		case 'J':
//			return 11;
//		case 'Q':
//			return 12;
//		case 'K':
//			return 13;
//		case 'A':
//			return 14;
//	}
//}

// check the hand pattern
int checkHand(char hand[5][2])
{
	int i;
	// patterns
	bool straight = true;
	bool flush = true;
	bool quadruple = false;
	bool triple = false;
	bool pair = false;
	bool doublepair = false;
	int conseq = 1;

	for(i=0; i<4; i++) {
		if(hand[i][1]!=hand[i+1][1])
			flush = false;
		if(hand[i][0]!=hand[i+1][0]+1)
			straight = false;
		if(hand[i][0]==hand[i+1][0]) {
			if(conseq==1) {
				if(!pair)
					pair = true;
				else
					doublepair = true;
			} else if(conseq==2)
				triple = true;
			else if(conseq==3)
				quadruple = true;
			conseq++;
		} else
			conseq =1;
	}
	if(straight && flush)
		return 8;
	else if(quadruple)
		return 7;
	else if(triple && doublepair)
		return 6;
	else if(flush)
		return 5;
	else if(straight)
		return 4;
	else if(triple)
		return 3;
	else if(doublepair)
		return 2;
	else if(pair)
		return 1;
	else
		return 0;
}

// if the hand patterns are the same, check which one is larger
int samePattern(int hand)
{
	int i;
	switch(hand) {
		case 8: case 4:
			if(black[0][0]<white[0][0])
				return WHITEWIN;
			else if(black[0][0]>white[0][0])
				return BLACKWIN;
			else
				return TIE;
		case 7:
			if(black[1][0]>white[1][0])
				return BLACKWIN;
			else if(black[1][0]<white[1][0])
				return WHITEWIN;
			else
				return TIE;
		case 6: case 3:
			if(black[2][0]>white[2][0])
				return BLACKWIN;
			else if(black[2][0]<white[2][0])
				return WHITEWIN;
			else
				return TIE;
		case 5: case 0:
			for(i=0; i<5; i++) {
				if(black[i][0]>white[i][0])
					return BLACKWIN;
				else if(black[i][0]<white[i][0])
					return WHITEWIN;
			}
			return TIE;
		case 2:
			int lpB, spB, sB, lpW, spW, sW;
			if(black[0][0]==black[1][0]) {
				lpB = black[0][0];
				if(black[2][0]==black[3][0]) {
					spB = black[2][0];
					sB = black[4][0];
				} else {
					spB = black[3][0];
					sB = black[2][0];
				}
			}
			else if(black[1][0]==black[2][0]) {
				sB = black[0][0];
				lpB = black[1][0];
				spB = black[3][0];
			}
			if(white[0][0]==white[1][0]) {
				lpW = white[0][0];
				if(white[2][0]==white[3][0]) {
					spW = white[2][0];
					sW = white[4][0];
				} else {
					spW = white[3][0];
					sW = white[2][0];
				}
			}
			else if(white[1][0]==white[2][0]) {
				sW = white[0][0];
				lpW = white[1][0];
				spW = white[3][0];
			}
			if(lpB>lpW) return BLACKWIN;
			else if(lpB<lpW) return WHITEWIN;
			else if(spB>spW) return BLACKWIN;
			else if(spB<spW) return WHITEWIN;
			else if(sB>sW) return BLACKWIN;
			else if(sB<sW) return WHITEWIN;
			else return TIE;
		case 1:
			int cmpW, cmpB;
			for(i=0; i<4; i++) {
				if(black[i][0]==black[i+1][0]) {
					cmpB = black[i][0];
					break;
				}
			}
			for(i=0; i<4; i++) {
				if(white[i][0]==white[i+1][0]) {
					cmpW = white[i][0];
					break;
				}
			}
			if(cmpB>cmpW) return BLACKWIN;
			else if(cmpB<cmpW) return WHITEWIN;
			i = 0;
			for(i=0; i<5; i++) {
				if(black[i][0]>white[i][0]) return BLACKWIN;
				if(black[i][0]<white[i][0]) return WHITEWIN;
			}
			return TIE;
	}
}

int compare(const void *a, const void *b)
{
	if(*(char *)a>*(char *)b) return -1;
	if(*(char *)a<*(char *)b) return 1;
	return 0;
}

int main()
{
	int i;
	int t;
	int blackHand;
	int whiteHand;
	char line[30];
	while(cin.getline(line, 30)) {
		if(line[0]==0)
			break;
		for(i=0; i<5; i++) {
			black[i][0] = line[3*i];
			switch(black[i][0]) {
				case 'T':
					black[i][0] = '9'+1;
					break;
				case 'J':
					black[i][0] = '9'+2;
					break;
				case 'Q':
					black[i][0] = '9'+3;
					break;
				case 'K':
					black[i][0] = '9'+4;
					break;
				case 'A':
					black[i][0] = '9'+5;
					break;
			}
			black[i][1] = line[3*i+1];
		}
		for(i=5; i<10; i++) {
			white[i-5][0] = line[3*i];
			switch(white[i-5][0]) {
				case 'T':
					white[i-5][0] = '9'+1;
					break;
				case 'J':
					white[i-5][0] = '9'+2;
					break;
				case 'Q':
					white[i-5][0] = '9'+3;
					break;
				case 'K':
					white[i-5][0] = '9'+4;
					break;
				case 'A':
					white[i-5][0] = '9'+5;
					break;
			}
			white[i-5][1] = line[3*i+1];
		}
		qsort((void *)black, 5, 2*sizeof(char), compare);
		qsort((void *)white, 5, 2*sizeof(char), compare);

		blackHand = checkHand(black);
		whiteHand = checkHand(white);

		if(blackHand>whiteHand)
			cout<<"Black wins."<<endl;
		else if(blackHand<whiteHand)
			cout<<"White wins."<<endl;
		else {
			t = samePattern(blackHand);
			if(t==BLACKWIN)
				cout<<"Black wins."<<endl;
			else if(t==WHITEWIN)
				cout<<"White wins."<<endl;
			else
				cout<<"Tie."<<endl;
		}
	}
	return 0;
}