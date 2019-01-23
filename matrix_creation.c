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
	j = 1;
	while (j < graph->rooms)
	{
		if (graph->links[0][j] == 1)
			graph->starts[i++] = j;
		j++;
	}
	graph->starts[i] = -1;
	return (i);
}

void	make_name_arr(t_graph *graph)
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

// void	make_path_arr(t_graph *graph)
// {
// 	int		i;
// 	int		i_p;
// 	t_path	*tmp;

// 	i = 0;
// 	tmp = graph->pathes;
// 	graph->p_num = graph->ant_amount == 1 ? 1 : graph->p_num;
// 	graph->ant_p = (int ***)ft_memalloc(sizeof(int **) * graph->p_num);
// 	while (i < graph->p_num)
// 	{
// 		i_p = 1;
// 		graph->ant_p[i] = (int **)ft_memalloc(sizeof(int *) * (tmp->p_val + 1));
// 		graph->ant_p[i][0] = (int *)ft_memalloc(sizeof(int) * 2);
// 		// graph->ant_p[i][0][0] = 0;
// 		dprintf(g_fd, "path #%d", i + 1);
// 		dprintf(g_fd, "%3d", graph->ant_p[i][0][0]);
// 		while (i_p < tmp->p_val + 1)
// 		{
// 			graph->ant_p[i][i_p] = (int *)ft_memalloc(sizeof(int) * 2);
// 			graph->ant_p[i][i_p][0] = tmp->path[i_p - 1];
// 			graph->ant_p[i][i_p][1] = 0;
// 			dprintf(g_fd, "%3d, %d", graph->ant_p[i][i_p][0],  graph->ant_p[i][i_p][1]);
// 			i_p++;
// 		}
// 		dprintf(g_fd, "\n");
// 		tmp = tmp->next;
// 		i++;
// 	}
// }