#include <stdio.h>
#include <string.h>

#define MAX_LEN 20
#define MAX_DEP (MAX_LEN+5)

char u[MAX_LEN], v[MAX_LEN], w[MAX_LEN], z[MAX_LEN], p[MAX_DEP][MAX_LEN];
size_t len_u, len_v, len_z;

bool solve_first_pos(char cur_str[], size_t len, int r)
{
	bool solve_next_pos(char[], size_t, size_t, int, size_t);
	
	if(r >= MAX_DEP)
		return false;
	
	p[r][0] = 'a';
	size_t tmp_len;
	for(size_t i = 1; i <= len_u; i++)
		if(strncmp(u+len_u-i, cur_str, tmp_len = (len >= i ? i : len)) == 0)
			if(solve_next_pos(cur_str, len, tmp_len, r, 1))
				return true;
	
	p[r][0] = 'b';
	for(size_t i = 1; i <= len_v; i++)
		if(strncmp(v+len_v-i, cur_str, tmp_len = (len >= i ? i : len)) == 0)
			if(solve_next_pos(cur_str, len, tmp_len, r, 1))
				return true;
	
	return false;
}

bool solve_next_pos(char cur_str[], size_t len, size_t pos, int r, size_t len_p)
{
	if(pos == len)
	{
		p[r][len_p] = '\0';
		if(strcmp(cur_str, p[r]) == 0)
			return false;
		//if(len_p == 1)
		//	return strchr(w, p[r][0]);	// this pruning is wrong! it causes me huge amount of time to debug!!
		if(strstr(w, p[r]) != 0)
			return true;
		if(solve_first_pos(p[r], len_p, r+1))
			return true;
		return false;
	}
	
	size_t tmp_len;
	if(strncmp(cur_str+pos, u, tmp_len = (len-pos >= len_u ? len_u : len-pos)) == 0)
	{
		p[r][len_p] = 'a';
		if(solve_next_pos(cur_str, len, pos+tmp_len, r, len_p+1))
			return true;
	}
	
	if(strncmp(cur_str+pos, v, tmp_len = (len-pos >= len_v ? len_v : len-pos)) == 0)
	{
		p[r][len_p] = 'b';
		if(solve_next_pos(cur_str, len, pos+tmp_len, r, len_p+1))
			return true;
	}
	
	return false;
}

bool solve()
{
	if(strstr(w, z) != 0)
		return true;
	
	len_u = strlen(u);
	len_v = strlen(v);
	len_z = strlen(z);
	if(len_u == 1 && len_v == 1)
	{
		if(u[0] == v[0])
			return (u[0] == 'a' && strchr(z, 'b') == 0) || (u[0] == 'b' && strchr(z, 'a') == 0);
		if(u[0] == 'a' && v[0] == 'b')
			return false;
		for(size_t i = 0; i < len_z; i++)
			p[0][i] = z[i] == 'a' ? 'b' : 'a';
		p[0][len_z] = '\0';
		return strstr(w, p[0]);
	}
	
	return solve_first_pos(z, len_z, 0);
}

int main()
{
	while(fgets(u, sizeof(u), stdin))
	{
		fgets(v, sizeof(v), stdin);
		fgets(w, sizeof(w), stdin);
		fgets(z, sizeof(z), stdin);
		u[strlen(u)-1] = v[strlen(v)-1] = w[strlen(w)-1] = z[strlen(z)-1] = 0;
		if(solve())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
