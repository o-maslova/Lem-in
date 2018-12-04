#include "lem_in.h"

t_link		*link_add(t_link *list, char *s, int pos)
{
	t_link *tmp;

	tmp = NULL;
	if (list->name == NULL && s)
	{
		list->name = ft_strdup(s);
		list->pos = pos;
		list->next = NULL;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_link *)ft_memalloc(sizeof(t_link));
		tmp->next->name = ft_strdup(s);
		tmp->next->pos = pos;
		tmp->next->next = NULL;
	}
	return (list);
}

t_coords	*vertex_create(char **arr, int pos)
{
	static int	i;
	t_coords	*vertex;

	vertex = NULL;
	if (arr)
	{
		vertex = (t_coords *)ft_memalloc(sizeof(t_coords));
		vertex->links = (t_link *)ft_memalloc(sizeof(t_link));
		vertex->links->name = NULL;
		vertex->name = ft_strdup(arr[0]);
		vertex->x = ft_atoi(arr[1]);
		vertex->y = ft_atoi(arr[2]);
		vertex->pos = i;
		if (pos == 1)
			vertex->is_start = 1;
		else if (pos == 2)
			vertex->is_end = 1;
		vertex->next = NULL;
	}
	i++;
	return (vertex);
}

void		add_vertex(t_coords **list, t_coords *vertex)
{
	t_coords *tmp;

	tmp = NULL;
	if (!(*list) && vertex)
		*list = vertex;
	else if (vertex)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = vertex;
	}
}
