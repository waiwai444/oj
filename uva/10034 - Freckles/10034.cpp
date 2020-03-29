
#include <stdio.h>
#include <math.h>

#define MAXV 101
#define MAXW 100000

typedef struct
{
	double point[MAXV][2];
	double weight_mat[MAXV][MAXV];	// weight matrix (complete graph))
	int nvertices;
} Graph;

Graph graph;

double prim()
{
	double total = 0.0;
	bool intree[MAXV];
	double weight[MAXV];	// the weights of vertices from the tree
	double cur_weight;
	int i, v, w;
	for(i = 0; i < graph.nvertices; ++i)
	{
		intree[i] = false;
		weight[i] = MAXW;
	}
	v = 0;
	weight[v] = 0;
	for(i = 0; i < graph.nvertices - 1; ++i)
	{
		intree[v] = true;
		for(w = 1; w < graph.nvertices; ++w)
		{
			cur_weight = graph.weight_mat[v][w];
			if(cur_weight < weight[w])
				weight[w] = cur_weight;
		}
		cur_weight = MAXW;
		for(w = 1; w < graph.nvertices; ++w)
		{
			if(!intree[w] && weight[w] < cur_weight)
			{
				v = w;
				cur_weight = weight[w];
			}
		}
		total += cur_weight;
	}
	return total;
}

int main()
{
	int t, i, j;
	scanf("%d", &t);
	while(t-- > 0)
	{
		scanf("%d", &graph.nvertices);
		for(i = 0; i < graph.nvertices; ++i)
			scanf("%lf%lf", &graph.point[i][0], &graph.point[i][1]);
		for(i = 0; i < graph.nvertices - 1; ++i)
		{
			for(j = i + 1; j < graph.nvertices; ++j)
			{
				double weight = sqrt((graph.point[i][0] - graph.point[j][0]) * (graph.point[i][0] - graph.point[j][0]) + (graph.point[i][1] - graph.point[j][1]) * (graph.point[i][1] - graph.point[j][1]));
				graph.weight_mat[i][j] = weight;
				graph.weight_mat[j][i] = weight;
			}
		}
		printf("%.2f\n", prim());
		if(t > 0)
			printf("\n");
	}
	return 0;
}
