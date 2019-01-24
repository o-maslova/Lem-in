#include "lem_in.h"

void	print_arr(int *arr, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		dprintf(g_fd, "%d ", arr[i++]); 
	}
	dprintf(g_fd, "\n");
}

void	clear_algo(t_algo **algo)
{
	free((*algo)->distances);
	free((*algo)->prev);
	free((*algo)->visited);
	free((*algo)->queue);
	free(*algo);
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

void	define_ant_and_path(t_graph *graph)
{
	int		i;
	int		ant;
	int		var;
	t_path	*tmp;

	i = 1;
	ant = graph->ant_amount;
	tmp = graph->pathes;
	while (ant > 1 && tmp)
	{
		if (tmp->next)
		{
			var = (tmp->next->p_val - tmp->p_val) * i++;
			ant = ant - var > 0 ? ant - var : 0;
			if (ant == 0)
				break ;
			tmp->next->ant = ant;
		}
		tmp = tmp->next;
	}
	i = ant == 0 ? i - 1 : i;
	if (i != graph->p_num)
		clear_path(&(tmp->next));
	graph->p_num = i;
}

void	algorithm(t_graph *graph)
{
	t_path	*variant;
	t_link	*path;
	t_algo	*algo;
	int		*used;

	algo = NULL;
	path = NULL;
	variant = NULL;
	used = (int *)ft_memalloc(sizeof(int) * ROOMS);
	initial(&algo, ROOMS);
	
	dprintf(g_fd, "ant_amount = %d\n", graph->ant_amount);
	dprintf(g_fd, "end = %d\n", graph->end_room);
	dprintf(g_fd, "rooms = %d\n", graph->rooms);
	
	while ((variant = deeper(algo, graph, used)) != NULL)
	{
		graph->p_num += add_path(&(graph->pathes), variant);
	}
	sort_path(graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	print_variants(g_fd, graph->pathes);
	make_name_arr(graph);
	graph->pathes->ant = graph->ant_amount;
	define_ant_and_path(graph);
	ant_output(graph);
	clear_algo(&algo);
	free(used);
}