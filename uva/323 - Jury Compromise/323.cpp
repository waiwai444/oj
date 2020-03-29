#include <stdio.h>
#include <string.h>

struct DPStruct
{
	bool has_value(int v) { return _value[v+400]; }
	unsigned char* get_jury(int v) { return _jury[v+400]; }
	int get_d_plus_p(int v) { return _d_plus_p[v+400]; }
	
	void set_value(int v) { _value[v+400] = true; }
	void set_jury(int v, unsigned char* j, int n) { memcpy(_jury[v+400], j, n*sizeof(unsigned char)); }
	void set_d_plus_p(int v, int s) { _d_plus_p[v+400] = s; }
private:
	bool _value[801];
	unsigned char _jury[801][20];
	int _d_plus_p[801];
};

DPStruct dptable[21];	// using different numbers of people

int main()
{
	int i, j, k, n, m, tc = 0;
	int p[200], d[200];
	unsigned char tmp_jury[20];
	while(scanf("%d%d", &n, &m), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d%d", &p[i], &d[i]);
		memset(dptable, 0, sizeof(dptable));

		dptable[0].set_value(0);
		dptable[0].set_d_plus_p(0, 0);
		dptable[1].set_value(p[0]-d[0]);
		tmp_jury[0] = 0;
		dptable[1].set_jury(p[0]-d[0], tmp_jury, 1);
		dptable[1].set_d_plus_p(p[0]-d[0], p[0]+d[0]);
		for(i = 1; i < n; i++)
		{
			for(j = (i+1 > m ? m : i+1); j >= 1; j--)
			{
				for(k = -380; k <= 380; k++)
				{
					if(dptable[j-1].has_value(k))
					{
						if(!dptable[j].has_value(k+p[i]-d[i]) || dptable[j-1].get_d_plus_p(k)+p[i]+d[i] > dptable[j].get_d_plus_p(k+p[i]-d[i]))
						{
							dptable[j].set_value(k+p[i]-d[i]);
							memcpy(tmp_jury, dptable[j-1].get_jury(k), (j-1)*sizeof(unsigned char));
							tmp_jury[j-1] = i;
							dptable[j].set_jury(k+p[i]-d[i], tmp_jury, j);
							dptable[j].set_d_plus_p(k+p[i]-d[i], dptable[j-1].get_d_plus_p(k)+p[i]+d[i]);
						}
					}
				}
			}
		}
		
		int r;
		for(k = 0; k <= 400; k++)
		{
			if(dptable[m].has_value(k) || dptable[m].has_value(-k))
			{
				if(dptable[m].get_d_plus_p(k) >= dptable[m].get_d_plus_p(-k))
					r = k;
				else if(dptable[m].get_d_plus_p(k) < dptable[m].get_d_plus_p(-k))
					r = -k;
				break;
			}
		}
		
		int D = 0, P = 0;
		unsigned char *jury = dptable[m].get_jury(r);
		for(i = 0; i < m; i++)
		{
			D += d[jury[i]];
			P += p[jury[i]];
		}
		printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", ++tc, P, D);
		for(i = 0; i < m; i++)
			printf(" %d", jury[i]+1);
		printf("\n\n");	
	}
	return 0;
}
