#include <stdio.h>
#include <math.h>
#include <algorithm>

int n, m;
double ball[8];

int main()
{
	int i, j;
	double width;
	double position[8], tmp_pos, left, right;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &m);
		for(i = 0; i < m; i++)
			scanf("%lf", &ball[i]);
		std::sort(ball, ball+m);
		width = 0x3f3f3f3f;
		do
		{
			left = 0;
			position[0] = ball[0];
			right = ball[0]+ball[0];
			for(i = 1; i < m; i++)
			{
				position[i] = 0;
				for(j = i-1; j >= 0; j--)
				{
					tmp_pos = position[j]+sqrt((ball[i]+ball[j])*(ball[i]+ball[j])-(ball[i]-ball[j])*(ball[i]-ball[j]));
					if(tmp_pos > position[i])
						position[i] = tmp_pos;
					if(position[i]+ball[i] > right)
						right = position[i]+ball[i];
					if(position[i]-ball[i] < left)
						left = position[i]-ball[i];
					if(right-left >= width)
						goto next;
				}
			}
			width = right-left;
			next:;
		} while(std::next_permutation(ball, ball+m));
		printf("%.3lf\n", width);
	}
	return 0;
}
