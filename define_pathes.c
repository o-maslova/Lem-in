#include "lem_in.h"

int		found_match(t_path *tmp, int *arr, int end)
{
	int		k;
	int		i;

	i = 0;
	k = 0;
	while (i < tmp->p_val)
	{
		if (arr[tmp->path[i][0]] == 0 && tmp->path[i][0] != end)
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

void		define_ant_step(t_graph *graph)
{
	int		ants;
	t_path	*tmp;

	ants = graph->ant_amount;
	tmp = graph->pathes;
	while (ants > 0)
	{
		ants--;
		tmp->ant_in_path++;
		tmp = tmp->next;
		if (tmp == NULL)
			tmp = graph->pathes;
	}
}