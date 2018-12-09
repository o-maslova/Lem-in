#include "lem_in.h"

t_vert		*search_by_pos(t_vert *graph, int pos)
{
	t_vert *tmp;

	tmp = graph;
	tmp = tmp->next;
	while (tmp)
	{
		dprintf(g_fd, "tmp = %s, is_visit %d\n", tmp->name, tmp->if_visit);
		if (tmp->pos == pos && !tmp->is_start)
		{
			if (tmp->if_visit == 0 || tmp->is_end)
			{
				return (tmp);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int			search_by_name(t_vert *graph, char *name)
{
	int		res;
	t_vert	*tmp;

	tmp = graph;
	// dprintf(g_fd, "name = %s\n", name);
	while (tmp)
	{
		res = ft_strcmp(tmp->name, name);
		// dprintf(g_fd, "tmp = %s, is_visit %d\n", tmp->name, tmp->if_visit);
		if (res == 0)
			return (tmp->pos);
		tmp = tmp->next;
	}
	return (-1);
}
