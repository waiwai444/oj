
#include <cstdio>

using namespace std;

inline void generate_blanks(int &num, int &counter)
{
	counter += num;
	while(num>0)
	{
		printf(" ");
		num--;
	}
}

int main()
{
	int counter;
	int leading_blanks;
	char word_buf[1024];
	int word_len;
	char ch;
	char next_ch;
	bool eof;

	counter = 0;
	word_len = 0;
	leading_blanks = 0;
	eof = false;
	//FILE *f;
	//f = fopen("test.txt", "r");
	if(scanf("%c", &ch)==EOF)
		return 0;
	while(true)
	{
		if(scanf("%c", &next_ch)==EOF)
			eof = true;
		if(ch==' ')
		{
			leading_blanks++;
		}
		else if(ch=='\n')
		{
			if(counter==0)	// blank line or empty line
			{
				printf("\n");
				leading_blanks = 0;
			}
			else if(next_ch=='\n' || next_ch==' ')
			{
				printf("\n");
				counter = 0;
				leading_blanks = 0;
			}
			else
			{
				leading_blanks++;
			}
		}
		else
		{
			word_buf[word_len++] = ch;
			if(next_ch==' ' || next_ch=='\n' || eof)
			{
				word_buf[word_len] = '\0';
				if(counter+leading_blanks+word_len<=72)
				{
					generate_blanks(leading_blanks, counter);
					printf("%s", word_buf);
					counter += word_len;
				}
				else if(counter==0 && word_len>72)
				{
					if(leading_blanks>0)
						printf("\n");
					printf("%s", word_buf);
					counter += word_len;
				}
				else
				{
					printf("\n%s", word_buf);
					leading_blanks = 0;
					counter = word_len;
				}
				word_len = 0;
			}
		}
		if(eof)
			break;
		ch = next_ch;
	}
	return 0;
}