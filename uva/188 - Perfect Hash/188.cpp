#include <stdio.h>
#include <string.h>
#include <algorithm>

int n;
unsigned int w[13], h[13];

int nc;
unsigned int cand[80];

unsigned int get_w(char *word)
{
	unsigned int r = 0;
	while(*word != '\0')
		r = r*32+*word++-'a'+1;
	return r;
}

bool check_conflict(unsigned int C)
{
	int i, j;
	bool ret = false;
	for(i = 0; i < n; i++)
		h[i] = C/w[i]%n;
	nc = 0;
	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)
			if(h[i] == h[j])
			{
				ret = true;
				cand[nc++] = std::min((C/w[i]+1)*w[i], (C/w[j]+1)*w[j]);
			}
	return ret;
}

unsigned int find_next_C()
{
	unsigned int C = 0;
	for(int i = 0; i < nc; i++)
		if(cand[i] > C)
			C = cand[i];
	return C;
}

unsigned int solve()
{
	int i;
	unsigned int C = (unsigned int)-1;
	for(i = 0; i < n; i++)
		if(w[i] < C)
			C = w[i];
	
	while(check_conflict(C))
		C = find_next_C();
	
	return C;
}

int main()
{
	char line[500], *word;
	while(fgets(line, sizeof(line), stdin))
	{
		line[strlen(line)-1] = 0;
		printf("%s\n", line);
		n = 0;
		word = strtok(line, " ");
		w[n++] = get_w(word);
		while(word = strtok(NULL, " "))
			w[n++] = get_w(word);
		
		printf("%u\n\n", solve());
	}
	return 0;
}
