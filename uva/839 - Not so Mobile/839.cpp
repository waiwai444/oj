#include <stdio.h>

bool equilibrium(int *weight)
{
	int wl, wr, dl, dr;
	bool el, er;
	el = er = true;
	scanf("%d%d%d%d", &wl, &dl, &wr, &dr);
	if(wl == 0)
	{
		el = equilibrium(&wl);
	}
	if(wr == 0)
	{
		er = equilibrium(&wr);
	}
	*weight = wl+wr;
	return el && er && wr*dr == wl*dl;
}

int main()
{
	int tc, weight;
	scanf("%d", &tc);
	while(tc--)
	{
		if(equilibrium(&weight))
			printf("YES\n");
		else
			printf("NO\n");
		if(tc)
			printf("\n");
	}
	return 0;
}