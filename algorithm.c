#include "lem_in.h"

void		print_path(t_path **path)
{
	int i;
	t_path *tmp;
	t_link *l_tmp;

	i = 0;
	tmp = *path;
	while (tmp)
	{
		dprintf(g_fd, "\nPATH #%d\n", i + 1);
		dprintf(g_fd, "__value__: %d\n", tmp->path_val);
		l_tmp = *(tmp->path);
		while (l_tmp)
		{
			dprintf(g_fd, "		vertex pos -------> %d\n", l_tmp->pos + 1);
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
		dprintf(g_fd, "link #%d		link pos = %d\n ", i, tmp->pos + 1);
		i++;
		tmp = tmp->next;
	}
}

int			remove_link(t_link **path)
{
	t_link	*tmp;
	int		pos;
	int		i;

	tmp = NULL;
	pos = 0;
	i = 0;
	if (*path)
	{
		tmp = *path;
		// tmp = tmp->next;
		while (tmp->next)
		{
			// dprintf(g_fd, "pos = %s\n", tmp->pos);
			if (!tmp->next->next)
				pos = tmp->pos;
			// free(tmp);
			tmp = tmp->next;
		}
		// str = ft_strdup(tmp->name);
		free(tmp);
	}
	return (pos);
}

void		func(t_vert **graph, t_link *link, t_path **variants, t_link **another)
{
	t_path			*tmp;
	t_vert			*add;
	// t_link			*l_tmp;
	// int				pos;
	static int		i;
	
	// dprintf(g_fd, "i = %d\n", i);
	if (link)
		dprintf(g_fd, "now link %s is working\n", link->name);
	if (link)
	{
		link->is_visit = 1;
		// vert->if_visit = 1;
		// tmp = vert->links;
		// dprintf(g_fd, "Node %s is working\n", link->name);
		if (link->pos < 0)
		{
			tmp = create_path(*another, i);
			add_path(variants, tmp);
			// l_tmp = dup_list(*another);
			// clear_link(another, &i);
			// *another = l_tmp;
			// initial(*graph, another, &i);
			print_path(variants);
		}
		else if ((add = search_by_pos(*graph, link->pos)) != NULL)
		{
			// dprintf(g_fd, "pos = %d, is_visit = %d\n", add->pos, add->if_visit);
			link_add_2(another, add->pos);
			add->if_visit = 1;
			++i;
			return (func(graph, add->links, variants, another));
		}
		// clear_visits(graph);
		return (func(graph, link->next, variants, another));
	}
	// initial(*graph, another, &i);
	// clear_link(another, &i);
	dprintf(g_fd, "\nEND\n");
}

void		initial(t_vert *start, t_link **another)
{
	*another = (t_link *)ft_memalloc(sizeof(t_link));
	(*another)->name = start->name;
	(*another)->pos = start->pos;
}

void		algorithm(t_vert **graph)
{
	t_path	*variants;
	t_link	*another;
	t_link	*l_tmp;
	// t_vert	*tmp;

	// variants = (t_path *)ft_memalloc(sizeof(t_path));
	// variants->path = (t_link *)ft_memalloc(sizeof(t_link));
	// another = (t_link *)ft_memalloc(sizeof(t_link));
	another = NULL;
	variants = NULL;
	// initial(*graph, &another);
	l_tmp = (*graph)->links;
	while (l_tmp)
	{
		initial(*graph, &another);
		if (l_tmp)
			dprintf(g_fd, "---LINK %s IS WORKING---\n", l_tmp->name);
		func(graph, l_tmp, &variants, &another);
		// dprintf(g_fd, "another - %s\n", another->name);
		// clear_visits(graph);
		l_tmp = l_tmp->next;

	}
	// vert = *graph;
	// vert = search_vertex(*graph, START);
	// 
}