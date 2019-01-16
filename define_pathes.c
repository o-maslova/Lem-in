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
	if (graph->pathes->next)
		val = graph->pathes->next->p_val - graph->pathes->p_val;
	else
		val = graph->pathes->p_val + 1;
	while (tmp)
	{
		k = found_match(tmp, arr, graph->end_room);
		if (k + 1 == tmp->p_val && (val < graph->ant_amount || graph->p_num == 0))
		{
			match(arr, tmp->path, tmp->p_val);
			if (tmp->next)
				val = tmp->next->p_val - tmp->p_val;
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
	while (i < graph->p_num)
	{
		k = 1;
		dprintf(g_fd, "path #%d\n", i + 1);
		dprintf(g_fd, "%3s = %d, ", "ant", graph->ant_p[i][0][0]);
		while (k < tmp->p_val + 1)
		{
			dprintf(g_fd, "%d, ", graph->ant_p[i][k][0]);
			k++;
		}
		tmp = tmp->next;
		dprintf(g_fd, "\n");
		i++;
	}
}

void		define_ant_and_path(t_graph *graph)
{
	int		i_p;
	// int		j;
	// int		val;
	int		ant;
	t_path	*tmp;

	ant = 0;
	tmp = graph->pathes;
	graph->p_num = graph->ant_amount == 1 ? 1 : graph->p_num;
	while (ant < graph->ant_amount)
	{
		i_p = 0;
		tmp = graph->pathes;
		while (ant < graph->ant_amount && i_p < graph->p_num)
		{
			if (ant >= graph->p_num && ant > tmp->p_val)
			{
				i_p++;
			}
			else
			{
				graph->ant_p[i_p][0][0] += 1;
				ant++;
				i_p++;
			}
			tmp = tmp->next;
		}
	}
	print_ants(graph);
}