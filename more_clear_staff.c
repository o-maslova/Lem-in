#include "lem_in.h"

void	clear_matrix(int **links, int amount)
{
	int i;

	i = 0;
	while (i < amount)
	{
		free(links[i]);
		i++;
	}
	free(links);
}

void	clear_3d_matrix(t_graph *graph)
{
	int		i;
	int		j;
	t_path	*tmp;

	i = 0;
	tmp = graph->pathes;
	while (i < graph->p_num)
	{
		j = 0;
		while (j < tmp->p_val + 1)
		{
			free(graph->ant_p[i][j]);
			j++;
		}
		free(graph->ant_p[i]);
		i++;
	}
	free(graph->ant_p);
}