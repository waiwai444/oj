#include <stdio.h>
#include <string.h>

char* my_strtok(char *str, char delim)
{
	static char* cur_ptr;
	char* p0;
	if(str != NULL)
		cur_ptr = str;
	p0 = cur_ptr;
	while(*cur_ptr != delim && *cur_ptr != '\0')
		cur_ptr++;
	*cur_ptr = '\0';
	cur_ptr++;
	return p0;
}

int main()
{
	int n;
	char l1[105], l2[105], *s1, *s2, *s3, *s4, *s5;
	scanf("%d", &n);
	fgets(l1, sizeof(l1), stdin);
	while(n--)
	{
		fgets(l1, sizeof(l1), stdin);
		fgets(l2, sizeof(l2), stdin);
		l1[strlen(l1)-1] = l2[strlen(l2)-1] = 0;
		s1 = my_strtok(l1, '<');
		s2 = my_strtok(NULL, '>');
		s3 = my_strtok(NULL, '<');
		s4 = my_strtok(NULL, '>');
		s5 = my_strtok(NULL, '\n');
		l2[strlen(l2)-3] = '\0';
		printf("%s%s%s%s%s\n%s%s%s%s%s\n", s1, s2, s3, s4, s5, l2, s4, s3, s2, s5);
	}
	return 0;
}
