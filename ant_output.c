#include "lem_in.h"

int		out_it(t_graph *graph, int ant, int lim)
{
	// int		j;
	int		done_with;
	int		that_ant;
	t_path	*tmp;
	
	done_with = 0;
	// lim = lim > graph->p_num ? lim - graph->p_num : 0;
	that_ant = lim + 1;
	while (that_ant <= ant)
	{
		tmp = graph->pathes;
		// while (tmp && lim-- > 0)
		// 	tmp = tmp->next;
		while (tmp && that_ant <= ant)
		{
			// j = tmp->j;
			// if (that_ant > tmp->ant)
			// 	tmp = tmp->next;
			if (tmp && tmp->path[tmp->j] < 0)
			{
				tmp->path[tmp->j] = -tmp->path[tmp->j];
				if (tmp->path[tmp->j] == graph->end_room)
					done_with++;
				dprintf(g_fd, "L%d-%s ", that_ant, graph->arr[tmp->path[tmp->j]]);
				that_ant++;
			}
			tmp->j -= 1;
			tmp = tmp->next;
		}
	}
	dprintf(g_fd, "\n");
	return (done_with);
}

void	match_rooms(t_path *path, int i, int ant)
{
	int		j;
	t_path	*tmp;

	tmp = path;
	if (ant <= path->ant)
		j = 0;
	else
		j = (path->k)++;
	while (j < path->p_val && j < i)
	{
		path->path[j] = -path->path[j];
		j++;
	}
}

void	ant_output(t_graph *graph)
{
	int		ant;
	int		done_with;
	t_path	*tmp;

	ant = 0;
	done_with = 0;
	while (done_with < graph->ant_amount)
	{
		tmp = graph->pathes;
		while (tmp)
		{
			if (tmp->i > 0 && graph->ant_amount > graph->p_num)
				match_rooms(tmp, tmp->i, ant);
			if (tmp->i < tmp->p_val)
				tmp->path[tmp->i] = -tmp->path[tmp->i];
			if (ant < graph->ant_amount)
				ant++;
			// if (tmp->path[0] < 0)
			// 	ant++;
			tmp->j = tmp->i;
			if (tmp->i < tmp->p_val - 1)
				tmp->i += 1;
			tmp = tmp->next;
		}
		done_with += out_it(graph, ant, done_with);
	}
}