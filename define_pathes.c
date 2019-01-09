#include "lem_in.h"

int		found_match(t_path *tmp, int *arr, int end)
{
	int		k;
	int		i;

	i = 0;
	k = 0;
	while (i < tmp->path_val)
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
	t_path	*prev;
	t_path	*tmp;
	t_path	*fr;

	tmp = graph->pathes;
	while (tmp)
	{
		k = found_match(tmp, arr, graph->end_room);
		if (k + 1 == tmp->path_val)
		{
			match(arr, tmp->path, tmp->path_val);
			prev = tmp;
			graph->pathes_num += 1;
			tmp = tmp->next;
		}
		else
		{
			fr = tmp->next;
			free(tmp);
			tmp = NULL;
			prev->next = fr;
			tmp = prev->next;
		}
	}
}