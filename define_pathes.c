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

void	remove_node(t_path *path)
{
	t_path *tmp;

	if (path->next->next)
	{
		tmp = path->next->next;
		free(path->next);
		path->next = tmp;
	}
	// return (path);
}

void	define_right_variants(t_graph *graph, int *arr)
{
	int		k;
	int		val;
	t_path	*prev;
	t_path	*tmp;
	// t_path	*fr;

	tmp = graph->pathes;
	if (graph->pathes->next)
		val = graph->pathes->next->p_val - graph->pathes->p_val;
	else
		val = graph->pathes->p_val + 1;
	while (tmp && graph->ant_amount > 1)
	{
		k = found_match(tmp, arr, graph->end_room);
		if (k + 1 == tmp->p_val && (val < graph->ant_amount || graph->p_num == 0))
		{
			match(arr, tmp->path, tmp->p_val);
			if (tmp->next)
				val = tmp->next->p_val - tmp->p_val;
			prev = tmp;
			graph->p_num += 1;
		}
		else
		{
			remove_node(prev);
			// fr = tmp->next;
			// free(tmp);
			// tmp = fr;
			// tmp = fr;
			// free(tmp);
		}
		tmp = tmp->next;
	}
}

void		define_ant_and_path(t_graph *graph)
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
			graph->max_i = tmp->p_val;
		}
		tmp = tmp->next;
	}
	i = ant == 0 ? i - 1 : i;
	if (i != graph->p_num)
		clear_path(&(tmp->next));
	graph->p_num = i;
}