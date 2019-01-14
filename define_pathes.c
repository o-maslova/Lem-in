#include "lem_in.h"

int		found_match(t_path *tmp, int *arr, int end)
{
	int		k;
	int		i;

	i = 0;
	k = 0;
	while (i < tmp->p_val)
	{
		if (arr[tmp->path[i]] == 0 && tmp->path[i] != end)
			k++;
		i++;
	}
	return (k);
}

void	define_right_variants(t_graph *graph, int *arr)
{
	int		k;
	int		val;
	t_path	*prev;
	t_path	*tmp;
	t_path	*fr;

	tmp = graph->pathes;
	val = graph->pathes->p_val + graph->ant_amount;
	while (tmp)
	{
		k = found_match(tmp, arr, graph->end_room);
		if (k + 1 == tmp->p_val && tmp->p_val < val)
		{
			match(arr, tmp->path, tmp->p_val);
			val = tmp->p_val + graph->ant_amount;
			prev = tmp;
			graph->p_num += 1;
			tmp = tmp->next;
		}
		else
		{
			k = 0;
			fr = tmp->next;
			// while (k < tmp->p_val)
			// 	free(tmp->path[k++]);
			free(tmp);
			tmp = NULL;
			prev->next = fr;
			tmp = prev->next;
		}
	}
}

void		print_ants(t_graph *graph)
{
	int i;
	int k;
	t_path *tmp;

	i = 0;
	tmp = graph->pathes;
	dprintf(g_fd, "\n");
	while (i < graph->ant_amount)
	{
		k = 0;
		dprintf(g_fd, "ant #%d\n", i + 1);
		while (k < tmp->p_val + 1)
		{
			dprintf(g_fd, "%3d, ", graph->ant_p[i][k]);
			k++;
		}
		tmp = tmp->next;
		if (tmp == NULL)
			tmp = graph->pathes;
		dprintf(g_fd, "\n");
		i++;
	}
}

void		define_ant_and_path(t_graph *graph)
{
	int		i;
	int		ant;
	t_path	*tmp;

	ant = 0;
	tmp = graph->pathes;
	graph->ant_p = (int **)ft_memalloc(sizeof(int *) * graph->ant_amount);
	while (ant < graph->ant_amount)
	{
		while (tmp && tmp->p_val > ant)
			tmp = tmp->next;
		tmp = tmp == NULL ? graph->pathes : tmp->next;
		i = 1;
		graph->ant_p[ant] = (int *)ft_memalloc(sizeof(int) * (tmp->p_val + 1));
		graph->ant_p[ant][0] = ant + 1;
		while (i < tmp->p_val + 1)
		{
			graph->ant_p[ant][i] = tmp->path[i - 1];
			i++;
		}
		ant++;
		tmp->ant_in_path++;
	}
	print_ants(graph);
}