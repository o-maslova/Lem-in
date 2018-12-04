#include "lem_in.h"

void		remove_vertex(t_coords *path)
{
	t_coords	*tmp;

	tmp = NULL;
	if (path)
	{
		tmp = path;
		while (tmp->next)
			tmp = tmp->next;
		clear_vertex(tmp);
		tmp = NULL;
	}
}

t_coords	*search_vertex(t_coords *list, int pos)
{
	t_coords *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->pos == pos)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		func(t_coords *list, t_coords *vert, t_coords *path)
{
	// t_coords *current;
	t_coords *tmp;
	t_coords *add;

	// current = NULL;
	if (vert && !vert->is_end)
	{
		tmp = vert->links;
		while (tmp)
		{
			if ((add = search_vertex(list, tmp->pos)) != NULL)
			{
				add_vertex(path, add);
				add->if_visit = 1;
				return (func(list, add, path));
				tmp = tmp->next;
			}
		}
		if (!tmp)
		{
			remove_vertex(path);
		}
	}
}

void		algorithm(t_coords *list, t_coords *path)
{
	t_coords *tmp;

	tmp = NULL;
	tmp = list;
	while (tmp)
	{
		func(list, tmp, path);
		tmp = tmp->next;
	}
}