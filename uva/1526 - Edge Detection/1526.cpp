#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct RLE{
	int value;
	int rl;
	int fstPos;
};

int main()
{
	int i, j;
	int temp;
	int diff, rl; 
	int curDiff;
	int width, total;
	int row, curSeq, uSeq, bSeq;
	RLE rle;
	vector<RLE> input;
	vector<RLE> output;
	while(1)
	{
		cin>>width;
		if(width==0)
			break;
		i = 0;
		total = 0;
		while(1)
		{
			cin>>rle.value>>rle.rl;
			if(rle.value==0 && rle.rl==0)
				break;
			rle.fstPos = total;
			total += rle.rl;
			input.push_back(rle);
		}
		diff = rl = -1;
		curSeq = 0;
		for(i=0; i<total; i++)
		{
			uSeq = bSeq = -1;
			curDiff = 0;
			row = i/width;
			if(i>input[curSeq].fstPos+input[curSeq].rl-1)
			{
				curSeq++;
			}
			if(i-width-1>=0 && i-width-1>=(row-1)*width)	// upper left neighbor
			{
				if(input[curSeq].fstPos>i-width-1)
				{
					for(j=curSeq-1; j>=0; j--)
					{
						if(input[j].fstPos<=i-width-1)
						{
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
			}
			if(i-width>=0)	// upper neighbor
			{
				if(input[curSeq].fstPos>i-width)
				{
					for(j=curSeq-1; j>=0; j--)
					{
						if(input[j].fstPos<=i-width)
						{
							uSeq = j;
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
				else
					uSeq = curSeq;
			}
			if(i-width+1>=0 && i-width+1<row*width)		// upper right neighbor
			{
				if(input[curSeq].fstPos>i-width+1)
				{
					for(j=curSeq-1; j>=0; j--)
					{
						if(input[j].fstPos<=i-width+1)
						{
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
			}
			if(i>row*width)		// left neighbor
			{
				if(input[curSeq].fstPos>=i)
				{
					for(j=curSeq-1; j>=0; j--)
					{
						if(input[j].fstPos<i)
						{
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
			}
			if(i+1<(row+1)*width)	// right neighbor
			{
				if(i>=input[curSeq].fstPos+input[curSeq].rl-1)
				{
					for(j=curSeq+1; j<input.size(); j++)
					{
						if(input[j].fstPos+input[j].rl-1>i)
						{
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
			}
			if(i+width-1<total && i+width>(row+1)*width)	// bottom left neighbor
			{
				if(input[curSeq].fstPos+input[curSeq].rl<i+width)
				{
					for(j=curSeq+1; j<input.size(); j++)
					{
						if(input[j].fstPos+input[j].rl>=i+width)
						{
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
			}
			if(i+width<total)	// bottom neighbor
			{
				if(input[curSeq].fstPos+input[curSeq].rl-1<i+width)
				{
					for(j=curSeq+1; j<input.size(); j++)
					{
						if(input[j].fstPos+input[j].rl-1>=i+width)
						{
							bSeq = j;
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
				else
					bSeq = curSeq;
			}
			if(i+width+1<total && i+width+1<(row+2)*width)	// bottom right neighbor
			{
				if(input[curSeq].fstPos+input[curSeq].rl-1<i+width+1)
				{
					for(j=curSeq+1; j<input.size(); j++)
					{
						if(input[j].fstPos+input[j].rl-1>=i+width+1)
						{
							temp = abs(input[j].value-input[curSeq].value);
							if(curDiff<temp)
								curDiff = temp;
							break;
						}
					}
				}
			}
			if(diff!=curDiff)
			{
				if(diff!=-1)
				{
					rle.value = diff;
					rle.rl = rl;
					output.push_back(rle);
				}
				diff = curDiff;
				rl = 1;
			}
			else
			{
				rl++;
			}

			// skip consecutive pixels
			if((i%width==0 || input[curSeq].fstPos<i) && input[curSeq].fstPos+input[curSeq].rl-1>i)
			{
				temp = input[curSeq].fstPos+input[curSeq].rl-i-1;
				if(uSeq==-1 || (input[uSeq].fstPos<i-width && input[uSeq].fstPos+input[uSeq].rl-1>i-width+1))
				{
					if(uSeq!=-1 && temp>input[uSeq].fstPos+input[uSeq].rl-(i-width)-1)
						temp = input[uSeq].fstPos+input[uSeq].rl-(i-width)-1;
					else if(uSeq==-1 && temp>(row+1)*width-i-1)
						temp = (row+1)*width-i-1;
					if(bSeq==-1 || (input[bSeq].fstPos<i+width && input[bSeq].fstPos+input[bSeq].rl-1>i+width+1))
					{
						if(bSeq!=-1 && temp>input[bSeq].fstPos+input[bSeq].rl-(i+width)-1)
							temp = input[bSeq].fstPos+input[bSeq].rl-(i+width)-1;
						else if(bSeq==-1 && temp>(row+1)*width-i-1)
							temp = (row+1)*width-i-1;
						if(temp-2>0)
						{
							rl += (temp-2);
							i += (temp-2);
						}
					}
				}
			}
		}

		if(diff!=-1)
		{
			rle.value = diff;
			rle.rl = rl;
			output.push_back(rle);
		}

		cout<<width<<endl;
		for(i=0; i<output.size(); i++)
		{
			cout<<output[i].value<<' '<<output[i].rl<<endl;
		}
		cout<<0<<' '<<0<<endl;
		input.clear();
		output.clear();
	}
	cout<<0<<endl;
	return 0;
}