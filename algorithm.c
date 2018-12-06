#include "lem_in.h"

void		print_path(t_path *path)
{
	static int i;
	t_path *tmp;
	t_link *l_tmp;

	tmp = path;
	while (tmp)
	{
		dprintf(g_fd, "\nPATH #%d\n", i);
		l_tmp = path->path;
		while (l_tmp)
		{
			dprintf(g_fd, "		vertex pos -------> %d\n", l_tmp->pos);
			l_tmp = l_tmp->next;
		}
		i++;
		tmp = tmp->next;
	}
}

void		print_link(t_link *link)
{
	static int i;
	t_link *tmp;

	tmp = link;
	while (tmp)
	{
		dprintf(g_fd, "link #%d		link pos = %d\n ", i, link->pos);
		i++;
		tmp = tmp->next;
	}
}

void		remove_link(t_link **path)
{
	t_link	*tmp;

	tmp = NULL;
	if (*path)
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

t_vert		*search_vertex(t_vert *graph, char *name)
{
	t_vert *tmp;

	tmp = graph;
	dprintf(g_fd, "name = %s\n", name);
	while (tmp)
	{
		dprintf(g_fd, "tmp = %s, is_visit %d\n", tmp->name, tmp->if_visit);
		if (((ft_strcmp(tmp->name, name)) == 0))
		{
			if (tmp->if_visit == 0 || tmp->is_end)
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void		func(t_vert *graph, t_vert *vert, t_path *variants, t_link *another)
{
	t_link			*tmp;
	t_vert			*add;
	static int		i;

	if (vert)
	{
		vert->if_visit = 1;
		tmp = vert->links;
		while (tmp)
		{
			if (vert->is_end)
			{
				add_path(&variants, another, i);
				print_path(variants);
				remove_link(&another);
				i = 0;
				break ;
				// return (func(graph, add, variants, another);
			}
			// dprintf(g_fd, "found\n");
			else if ((add = search_vertex(graph, tmp->name)) != NULL)
			{
				link_add(&another, NULL, add->pos);
				dprintf(g_fd, "pos = %d, is_visit = %d\n", add->pos, add->if_visit);
				add->if_visit = 1;
				++i;
				return (func(graph, add, variants, another));
			}
			tmp = tmp->next;
		}
		// if (!tmp)
		// {
		// 	--i;
		// 	remove_link(another);
		// }
	}
}

void		algorithm(t_vert **graph)
{
	t_path	*variants;
	t_link	*another;
	t_link	*l_tmp;
	t_vert	*tmp;

	another = (t_link *)ft_memalloc(sizeof(t_link));
	another->name = (*graph)->name;
	another->pos = (*graph)->pos;
	variants = NULL;
	tmp = *graph;
	while (tmp)
	{
		l_tmp = tmp->links;
		func(*graph, tmp, variants, another);

	}
	// vert = *graph;
	// vert = search_vertex(*graph, START);
	// 
}