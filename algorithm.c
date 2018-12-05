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

void		remove_link(t_link *path)
{
	t_link	*tmp;

	tmp = NULL;
	if (path)
	{
		tmp = path;
		while (tmp->next)
			tmp = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

t_vert	*search_vertex(t_vert *list, int pos)
{
	t_vert *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->pos == pos && tmp->if_visit == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		func(t_vert *graph, t_vert *vert, t_path *variants)
{
	t_link			*another;
	// t_link			*node;
	t_link			*tmp;
	t_vert			*add;
	static int		i;

	another = NULL;
	if (vert)
	{
		tmp = vert->links;
		while (tmp)
		{
			if (vert->is_end)
			{
				// another = dup_list(path);
				add_path(&variants, another, i);
				print_path(variants);
				i = 0;
			}
			if ((add = search_vertex(graph, tmp->pos)) != NULL)
			{
				link_add(&another, NULL, add->pos);
				// add_vertex(path, add);
				add->if_visit = 1;
				++i;
				return (func(graph, add, variants));
				tmp = tmp->next;
			}
		}
		if (!tmp)
		{
			--i;
			remove_link(another);
		}
	}
}

void		algorithm(t_vert **graph)
{
	t_path	*variants;
	t_vert	*vert;

	// variants = (t_link *)ft_memmalloc(sizeof(t_link));
	// variants->name = NULL;
	// variants = link_add(variants, path->name, path->pos);
	// print_link(*path);
	// print_graph(vrt);
	variants = NULL;
	// vert = graph;
	vert = search_vertex(*graph, START);
	while (vert)
	{
		func(*graph, vert, variants);
		vert = vert->next;
	}
}