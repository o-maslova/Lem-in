#include "lem_in.h"

void		match(int *arr, int *path, int amount)
{
	int i;

	i = 0;
	while (i < amount - 1)
	{
		arr[path[i]] = -1;
		i++;
	}
}

void		match_column(int **links, int k, int amount)
{
	int i;

	i = 0;
	while (i < amount)
	{
		links[i][k] = -1;
		i++;
	}
}

void		unmatch(t_graph *graph, int limit)
{
	int		k;
	int		i;
	int		j;

	i = 0;
	while (i < graph->rooms)
	{
		j = 0;
		k = 0;
		while (j < graph->rooms)
		{
			if (graph->links[i][j] == -1)
			{
				if (j == graph->starts[k] && k <= limit)
					k++;
				else
					graph->links[i][j] = 1;
			}
			j++;
		}
		i++;
	}
}
