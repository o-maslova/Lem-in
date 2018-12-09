#include "lem_in.h"

void		link_add_2(t_link **list, int pos)
{
	t_link *tmp;

	tmp = NULL;
	if (!(*list)->name)
	{
		(*list)->pos = pos;
		// dprintf(g_fd, "POS = %d\n", (*list)->pos);
		(*list)->next = NULL;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_link *)ft_memalloc(sizeof(t_link));
		tmp->next->pos = pos;
		dprintf(g_fd, "POS = %d\n", tmp->next->pos);
		tmp->next->next = NULL;
	}
}

void		link_add_1(t_vert *graph, t_link **list, char *s)
{
	t_link *tmp;

	tmp = NULL;
	if (!(*list)->name)
	{
		(*list)->name = ft_strdup(s);
		(*list)->pos = search_by_name(graph, s);
		// dprintf(g_fd, "POS = %d\n", (*list)->pos);
		(*list)->next = NULL;
	}
	else
	{
		tmp = *list;
		if (tmp->next)
			while (tmp->next)
				tmp = tmp->next;
		tmp->next = (t_link *)ft_memalloc(sizeof(t_link));
		tmp->next->name = ft_strdup(s);
		tmp->next->pos = search_by_name(graph, s);
		tmp->next->next = NULL;
	}
}

t_vert		*vertex_create(char **arr, int pos)
{
	static int	i;
	t_vert	*vrt;

	vrt = NULL;
	if (arr)
	{
		vrt = (t_vert *)ft_memalloc(sizeof(t_vert));
		vrt->links = (t_link *)ft_memalloc(sizeof(t_link));
		// vrt->links->name = NULL;
		vrt->name = ft_strdup(arr[0]);
		vrt->x = ft_atoi(arr[1]);
		vrt->y = ft_atoi(arr[2]);
		vrt->is_start = pos == 1 ? 1 : 0;
		vrt->is_end = pos == 2 ? 1 : 0;
		if (pos == 1 || pos == 2)
			vrt->pos = i * -1;
		// else if (pos == 2)
		// 	vrt->pos = -2;
		else
			vrt->pos = i;
		vrt->next = NULL;
	}
	i++;
	return (vrt);
}

// void		add_vertex(t_vert **graph, t_vert *new) //with sort
// {
// 	t_vert *tmp;
// 	t_vert *tmp2;

// 	tmp = NULL;
// 	tmp2 = NULL;
// 	dprintf(g_fd, "push front\n");
// 	if (!(*graph) && new)
// 		*graph = new;
// 	else if (new)
// 	{
// 		tmp = *graph;
// 		while (tmp->next && tmp->x < new->x)
// 		{
// 			tmp2 = tmp;
// 			tmp = tmp->next;
// 		}
// 		new->next = tmp;
// 		if (tmp2)
// 			tmp2->next = new;
// 		else
// 			*graph = new;
// 	}
// }

void		add_vertex(t_vert **graph, t_vert *new) //start is first
{
	t_vert *tmp;
	t_vert *tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (!(*graph) && new)
		*graph = new;
	else if (new->is_start)
	{
		new->next = *graph;
		*graph = new;
	}
	else
	{
		tmp = *graph;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_link		**dup_list(t_link *list, t_link **new_path)
{
	// t_link *new_path;
	t_link *tmp;
	// t_link *tmp2;

	// new_path = (t_link *)ft_memalloc(sizeof(t_link));
	if (list)
	{
		tmp = list;
		// tmp2 = new_path;
		*new_path = (t_link *)ft_memalloc(sizeof(t_link));
		while (tmp)
		{
			// if (tmp->is_start == 1)
			// 	tmp2->is_start = 1;
			// tmp2->name = NULL;
			// tmp2->pos = tmp->pos;
			link_add_2(new_path, tmp->pos);
			dprintf(g_fd, "new_list pos %d\n", (*new_path)->pos);
			// tmp2 = tmp2->next;
			tmp = tmp->next;

		}
		// tmp2->next = NULL;
	}
	return (new_path);
}

t_path		*create_path(t_link *link, int val)
{
	t_link *l_tmp;
	t_path *tmp;

	tmp = NULL;
	if (link)
	{
		tmp = (t_path *)ft_memalloc(sizeof(t_path));
		tmp->path = (t_link **)ft_memalloc(sizeof(t_link *));
		tmp->path = dup_list(link, tmp->path);
		l_tmp = *(tmp->path);
		while (l_tmp)
		{
			dprintf(g_fd, "node #%d\n", l_tmp->pos);
			l_tmp = l_tmp->next;
		}
		// tmp->path = link;
		tmp->path_val = val;
		tmp->next = NULL;
	}
	return (tmp);
}

void		add_path(t_path **variants, t_path *path)
{
	t_path *tmp;

	tmp = NULL;
	if (!(*variants))
	{
		dprintf(g_fd, "val = %d\n", path->path_val);
		*variants = path;
	}
	else
	{
		dprintf(g_fd, "val = %d\n", path->path_val);
		tmp = *variants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = path;
	}
}
