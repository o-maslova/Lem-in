#include "lem_in.h"

void		link_add(t_link **list, char *s, int pos)
{
	t_link *tmp;

	tmp = NULL;
	if ((*list)->name == NULL)
	{
		(*list)->name = ft_strdup(s);
		(*list)->pos = pos;
		(*list)->next = NULL;
	}
	else
	{
		tmp = (*list);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_link *)ft_memalloc(sizeof(t_link));
		tmp->next->name = ft_strdup(s);
		tmp->next->pos = pos;
		tmp->next->next = NULL;
	}
	// return (list);
}

t_vert	*vertex_create(char **arr, int pos)
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
		vrt->pos = i;
		if (pos == 1)
			vrt->is_start = 1;
		else if (pos == 2)
			vrt->is_end = 1;
		vrt->next = NULL;
	}
	i++;
	return (vrt);
}

void		add_vertex_front(t_vert **graph, t_vert *new)
{
	t_vert *tmp;
	t_vert *tmp2;

	tmp = NULL;
	if (new->is_start == 1)
		START = new->pos;
	if (!(*graph) && new)
		*graph = new;
	else if (new)
	{
		tmp = *graph;
		while (tmp->next && tmp->x < new->x)
			tmp = tmp->next;
		tmp2 = tmp->next;
		new->next = tmp2;
		tmp->next = new;
	}
}

void		add_vertex_back(t_vert **graph, t_vert *new)
{
	t_vert *tmp;
	t_vert *tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (new->is_start == 1)
			START = new->pos;
	if (!(*graph) && new)
		*graph = new;
	else if (new)
	{
		tmp = *graph;
		while (tmp->next && tmp->x > new->x)
			tmp = tmp->next;
		tmp2 = tmp->next;
		new->next = tmp2;
		tmp->next = new;
	}
}

void		add_path(t_path **variants, t_link *path, int val)
{
	t_path *tmp;

	tmp = NULL;
	if (!path)
		return ;
	if (!(*variants))
	{
		*variants = (t_path *)ft_memalloc(sizeof(t_path));
		(*variants)->path = path;
		(*variants)->path_val = val;
		(*variants)->next = NULL;
	}
	else
	{
		tmp = *variants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_path *)ft_memalloc(sizeof(t_path));
		tmp->next->path = path;
		tmp->next->path_val = val;
		tmp->next = NULL;
	}
}

t_link	*dup_list(t_link *list)
{
	t_link *new_path;
	t_link *tmp;
	t_link *tmp2;

	new_path = NULL;
	if (list)
	{
		tmp = list;
		tmp2 = new_path;
		while (tmp)
		{
			tmp2 = (t_link *)ft_memalloc(sizeof(t_link));
			// if (tmp->is_start == 1)
			// 	tmp2->is_start = 1;
			link_add(&tmp2, NULL, tmp->pos);
			tmp = tmp->next;
		}
	}
	return (new_path);
}
