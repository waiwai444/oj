#include <stdio.h>

char in[13];

inline bool judge(char up, char down, char left, char front, char right, char back)
{
	return up == in[6] && down == in[11] && 
		(left == in[8] && front == in[7] && right == in[9] && back == in[10] ||
		left == in[7] && front == in[9] && right == in[10] && back == in[8] || 
		left == in[9] && front == in[10] && right == in[8] && back == in[7] || 
		left == in[10] && front == in[8] && right == in[7] && back == in[9]);		
}

int main()
{
	while(scanf("%s", in) != EOF)
	{
		if(judge(in[0], in[5], in[2], in[1], in[3], in[4]) || 
			judge(in[5], in[0], in[3], in[1], in[2], in[4]) || 
			judge(in[1], in[4], in[2], in[5], in[3], in[0]) || 
			judge(in[4], in[1], in[2], in[0], in[3], in[5]) || 
			judge(in[2], in[3], in[5], in[1], in[0], in[4]) || 
			judge(in[3], in[2], in[1], in[5], in[4], in[0]))
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	return 0;
}
