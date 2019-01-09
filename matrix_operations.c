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
				{
					k++;
				}
				else
					graph->links[i][j] = 1;
			}
			j++;
		}
		i++;
	}
}

int		create_start_matrix(t_graph *graph)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < graph->rooms)
	{
		if (graph->links[0][i] == 1)
			count++;
		i++;
	}
	graph->starts = (int *)ft_memalloc(sizeof(int) * (count + 1));
	i = 0;
	j = 0;
	while (j < graph->rooms)
	{
		if (graph->links[0][j] == 1)
			graph->starts[i++] = j;
		j++;
	}
	graph->starts[i] = -1;
	return (i);
}

void	make_arr(t_graph *graph)
{
	t_vert	*tmp;

	tmp = graph->graph;
	graph->arr = (char **)ft_memalloc(sizeof(char *) * (graph->rooms + 1));
	while (tmp)
	{
		graph->arr[tmp->pos] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	graph->arr[graph->rooms] = 0;
}