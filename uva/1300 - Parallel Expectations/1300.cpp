#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

#define MOV_R1 0
#define MOV_R2 1
#define ADD 2
#define SUB 3
#define MOV_VAR 4
#define IMMEDIATE ((unsigned char)-1)

struct instruction_t
{
	char inst;
	unsigned char var;
	unsigned char num;
} inst_set[2][101];

int inst_num[2];

struct variable_t
{
	char name[21];
	unsigned char idx;
} var_set[10];

int var_num;

struct dp_state_t
{
	double e[10], e_r1[2], e_r2[2];
} dp[101][101];

double prob[101][101];

void str_to_lower(char *p)
{
	while(*p != '\0')
	{
		*p = tolower(*p);
		++p;
	}
}

char *l_trim(char *p)
{
	while(*p != '\0' && !isgraph(*p))
		++p;
	return p;
}

bool cmp_var(const variable_t &var1, const variable_t &var2)
{
	return strcmp(var1.name, var2.name) < 0;
}

int handle_variable(const char *var)
{
	for(int i = 0; i < var_num; i++)
		if(strcmp(var_set[i].name, var) == 0)
			return i;
	strcpy(var_set[var_num].name, var);
	var_set[var_num].idx = var_num;
	return var_num++;
}

void read_programs()
{
	int i, j, cnt;
	char command[100], *ptr, *dest, *operand1, op, *operand2;
	var_num = 0;
	for(i = 0; i < 2; i++)
	{
		cnt = 0;
		while(fgets(command, 100, stdin))
		{
			if(*(ptr = l_trim(command)) == '\0')
				continue;
			dest = ptr;
			while(isalnum(*ptr)) ++ptr;
			*ptr++ = '\0';
			str_to_lower(dest);
			if(strcmp(dest, "end") == 0)
				break;
			while(!isalnum(*ptr)) ++ptr;
			operand1 = ptr++;
			while(isalnum(*ptr)) ++ptr;
			op = '\0';
			if(*ptr == '+') op = '+';
			else if(*ptr == '-') op = '-';
			*ptr++ = '\0';
			while(!isalnum(*ptr))
			{
				if(!op)
				{
					if(*ptr == '+') op = '+';
					else if(*ptr == '-') op = '-';
				}
				++ptr;
			}
			operand2 = ptr++;
			while(isalnum(*ptr)) ++ptr;
			*ptr = '\0';
			str_to_lower(operand1);
			str_to_lower(operand2);

			++cnt;
			inst_set[i][cnt].inst = MOV_R1;
			if(isdigit(operand1[0]))
			{
				inst_set[i][cnt].var = IMMEDIATE;
				inst_set[i][cnt].num = atoi(operand1);
			}
			else
			{
				str_to_lower(operand1);
				inst_set[i][cnt].var = handle_variable(operand1);
			}
			++cnt;
			inst_set[i][cnt].inst = MOV_R2;
			if(isdigit(operand2[0]))
			{
				inst_set[i][cnt].var = IMMEDIATE;
				inst_set[i][cnt].num = atoi(operand2);
			}
			else
			{
				str_to_lower(operand2);
				inst_set[i][cnt].var = handle_variable(operand2);
			}
			++cnt;
			inst_set[i][cnt].inst = (op == '+' ? ADD : SUB);
			++cnt;
			inst_set[i][cnt].inst = MOV_VAR;
			inst_set[i][cnt].var = handle_variable(dest);
		}
		inst_num[i] = cnt;
	}
	std::sort(var_set, var_set+var_num, cmp_var);
	/*for(i = 1; i <= inst_num[0]; i += 4)
	{
		printf("%d R1, %d\n", inst_set[0][i].inst, inst_set[0][i].var);
		printf("%d R2, %d\n", inst_set[0][i+1].inst, inst_set[0][i+1].var);
		printf("%d R1, R2\n", inst_set[0][i+2].inst);
		printf("%d %d, R1\n", inst_set[0][i+3].inst, inst_set[0][i+3].var);
	}
	for(i = 1; i <= inst_num[1]; i += 4)
	{
		printf("%d R1, %d\n", inst_set[1][i].inst, inst_set[1][i].var);
		printf("%d R2, %d\n", inst_set[1][i+1].inst, inst_set[1][i+1].var);
		printf("%d R1, R2\n", inst_set[1][i+2].inst);
		printf("%d %d, R1\n", inst_set[1][i+3].inst, inst_set[1][i+3].var);
	}*/
}

void execute(int i, int j, int p, dp_state_t *res)
{
	int i0 = i, j0 = j;
	const instruction_t &inst = inst_set[p][p == 0 ? i0-- : j0--];
	memcpy(res, &dp[i0][j0], sizeof(dp_state_t));
	switch(inst.inst)
	{
		case MOV_R1:
			if(inst.var == IMMEDIATE)
				res->e_r1[p] = inst.num;
			else
				res->e_r1[p] = dp[i0][j0].e[inst.var];
			break;
		case MOV_R2:
			if(inst.var == IMMEDIATE)
				res->e_r2[p] = inst.num;
			else
				res->e_r2[p] = dp[i0][j0].e[inst.var];
			break;
		case ADD:
			res->e_r1[p] = dp[i0][j0].e_r1[p]+dp[i0][j0].e_r2[p];
			break;
		case SUB:
			res->e_r1[p] = dp[i0][j0].e_r1[p]-dp[i0][j0].e_r2[p];
			break;
		case MOV_VAR:
			res->e[inst.var] = dp[i0][j0].e_r1[p];
			break;
	}
}

void compute()
{
	int i, j, k;
	double p1, p2;
	dp_state_t st1, st2;
	prob[0][0] = 1;
	for(i = 1; i <= inst_num[0]; i++)
	{
		execute(i, 0, 0, &dp[i][0]);
		prob[i][0] = (inst_num[1] > 0 ? prob[i-1][0]/2 : 1);
	}
	for(j = 1; j <= inst_num[1]; j++)
	{
		execute(0, j, 1, &dp[0][j]);
		prob[0][j] = (inst_num[0] > 0 ? prob[0][j-1]/2 : 1);
	}
	for(i = 1; i <= inst_num[0]; i++)
	{
		for(j = 1; j <= inst_num[1]; j++)
		{
			execute(i, j, 0, &st1);
			execute(i, j, 1, &st2);
			p1 = (j < inst_num[1] ? prob[i-1][j]/2 : prob[i-1][j]);
			p2 = (i < inst_num[0] ? prob[i][j-1]/2 : prob[i][j-1]);
			prob[i][j] = p1+p2;
			for(k = 0; k < var_num; k++)
				dp[i][j].e[k] = (st1.e[k]*p1+st2.e[k]*p2)/prob[i][j];
			for(k = 0; k < 2; k++)
			{
				dp[i][j].e_r1[k] = (st1.e_r1[k]*p1+st2.e_r1[k]*p2)/prob[i][j];
				dp[i][j].e_r2[k] = (st1.e_r2[k]*p1+st2.e_r2[k]*p2)/prob[i][j];
			}
		}
	}
	/*for(i = 0; i <= inst_num[0]; i++)
	{
		for(j = 0; j <= inst_num[1]; j++)
			printf("%lf ", prob[i][j]);
		printf("\n");
	}*/
}

void output()
{
	int i;
	for(i = 0; i < var_num; i++)
		printf("%.4lf\n", dp[inst_num[0]][inst_num[1]].e[var_set[i].idx]);
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		read_programs();
		compute();
		output();
		printf("\n");
	}
	return 0;
}
