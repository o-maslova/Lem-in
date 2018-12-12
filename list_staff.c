#include "lem_in.h"

t_link		*create_link(int pos)
{
	t_link *node;

	node = (t_link *)ft_memalloc(sizeof(t_link));
	node->pos = pos;
	node->next = NULL;
	return (node);
}

void		add_link(t_link **path, int pos)
{
	t_link *tmp;

	tmp = NULL;
	if (!(*path))
		*path = create_link(pos);
	else
	{
		tmp = *path;
		if (tmp->next)
			while (tmp->next)
				tmp = tmp->next;
		tmp->next = create_link(pos);
		// dprintf(g_fd, "POS = %d\n", tmp->pos);
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
		vrt->name = ft_strdup(arr[0]);
		vrt->x = ft_atoi(arr[1]);
		vrt->y = ft_atoi(arr[2]);
		vrt->is_start = pos == 1 ? 1 : 0;
		vrt->is_end = pos == 2 ? 1 : 0;
		// if (pos == 1 || pos == 2)
			// vrt->pos = i * -1;
		// else if (pos == 2)
		// 	vrt->pos = -2;
		// else
		vrt->pos = i;
		g_amount = vrt->pos;
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

int			count_elem(t_link *list)
{
	int		res;
	t_link	*tmp;

	res = 0;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			res++;
			tmp = tmp->next;
		}
	}
	return (res);
}

t_path		*create_path(t_link *link)
{
	t_link	*l_tmp;
	t_path	*tmp;
	int		i;

	tmp = NULL;
	if (link)
	{
		tmp = (t_path *)ft_memalloc(sizeof(t_path));
		i = count_elem(link);
		tmp->path_val = i;
		tmp->path = (int *)ft_memalloc(sizeof(int) * (i + 1));
		l_tmp = link;
		i = 0;
		while (l_tmp)
		{
			tmp->path[i] = l_tmp->pos;
			l_tmp = l_tmp->next;
			i++;
		}
		// tmp->path[i] = -1;
		tmp->next = NULL;
	}
	// print_path_2(tmp);
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
