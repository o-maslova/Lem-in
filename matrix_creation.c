#include "lem_in.h"

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

void	make_path_arr(t_graph *graph)
{
	int		i;
	int		k;
	t_path	*tmp;

	i = 0;
	tmp = graph->pathes;
	graph->p_arr = (int **)ft_memalloc(sizeof(int *) * (graph->p_num + 1));
	graph->output = (int **)ft_memalloc(sizeof(int *) * graph->p_num);
	while (tmp)
	{
		k = 0;
		graph->p_arr[i] = (int *)ft_memalloc(sizeof(int) * (tmp->path_val + 1));
		graph->output[i] = (int *)ft_memalloc(sizeof(int) * tmp->path_val);
		while (tmp->path[k] != graph->end_room)
		{
			graph->p_arr[i][k] = tmp->path[k];
			k++;
		}
		graph->p_arr[i][k] = tmp->path[k];
		graph->p_arr[i][++k] = -1;
		tmp = tmp->next;
		i++;
	}
	graph->p_arr[i] = (int *)ft_memalloc(sizeof(int));
	graph->p_arr[i][0] = -1;
}

void	make_arrays(t_graph *graph)
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
	make_path_arr(graph);
}