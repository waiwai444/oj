#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *p,const void *q)
{
	return (*(int*)p)-(*(int*)q);
}

int main()
{
	int tc, i,j,templen,cur,n;
	char temp[100];
	char digit;
	int tel[100000];
	int count;
	int outputcount;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			tel[i]=0;
			scanf("%s",temp);
			templen=strlen(temp);
			for(j=0;j<templen;j++)
			{
				switch(temp[j])
				{
				case '0':
					digit='0';
					break;
				case '1':
					digit='1';
					break;
				case '2':
				case 'A':
				case 'B':
				case 'C':
					digit='2';
					break;
				case '3':
				case 'D':
				case 'E':
				case 'F':
					digit='3';
					break;
				case '4':
				case 'G':
				case 'H':
				case 'I':
					digit='4';
					break;
				case '5':
				case 'J':
				case 'K':
				case 'L':
					digit='5';
					break;
				case '6':
				case 'M':
				case 'N':
				case 'O':
					digit='6';
					break;
				case '7':
				case 'P':
				case 'R':
				case 'S':
					digit='7';
					break;
				case '8':
				case 'T':
				case 'U':
				case 'V':
					digit='8';
					break;
				case '9':
				case 'W':
				case 'X':
				case 'Y':
					digit='9';
					break;
				default:
					continue;
				}
				tel[i]=tel[i]*10+digit-'0';
			}
		}
		qsort(tel,n,sizeof(int),compare);
		cur=tel[0];
		count=1;
		outputcount=0;
		for(i=1;i<n;i++)
		{
			if(cur!=tel[i])
			{
				if(count>1)
				{
					printf("%.3d-%.4d %d\n",cur/10000,cur%10000,count);
					outputcount++;
				}
				cur=tel[i];
				count=1;
			}
			else
				count++;
		}
		if(count>1)
		{
			printf("%.3d-%.4d %d\n",cur/10000,cur%10000,count);
			outputcount++;
		}
		if(outputcount==0)
			printf("No duplicates.\n");
		if(tc > 0)
			printf("\n");
	}
	return 0;
}