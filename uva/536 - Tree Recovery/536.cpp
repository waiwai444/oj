#include <stdio.h>
#include <string.h>

char preord[27], inord[27], postord[27];

void recur(int pre_begin, int pre_end, int in_begin, int &post_idx)
{
	int i, in_mid, in_end;
	char root = preord[pre_begin];
	
	if(pre_begin > pre_end)
		return;
	if(pre_begin == pre_end)
	{
		postord[post_idx++] = root;
		return;
	}
	
	in_end = in_begin+pre_end-pre_begin;
	for(i = in_begin; i <= in_end; i++)
	{
		if(inord[i] == root)
		{
			in_mid = i;
			break;
		}
	}
	recur(pre_begin+1, pre_begin+in_mid-in_begin, in_begin, post_idx);
	recur(pre_begin+in_mid-in_begin+1, pre_end, in_mid+1, post_idx);
	postord[post_idx++] = root;
}

int main()
{
	int len, post_idx;
	while(scanf("%s%s", preord, inord) != EOF)
	{
		len = strlen(preord);
		post_idx = 0;
		recur(0, len-1, 0, post_idx);
		postord[len] = '\0';
		printf("%s\n", postord);
	}
	return 0;
}
